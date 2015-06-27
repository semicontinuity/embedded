// =============================================================================
//
// =============================================================================

#include "services/temperature_reader.h"
#include "buffer.h"
#include "modbus_rtu_driver.h"
#include "modbus_server.h"
#include "drivers/out/rts.h"

#include "drivers/comm/onewire__bus.h"

#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/util/bcd.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <cpu/avr/int1.h>


void temperature_reader__reading__on_changed(void) {
    display__render_packed((uint8_t)uint9_to_bcd(temperature_reader__reading >> 8));
}

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    display__init();
//    int1__init();
//    rts__init();
    onewire__bus__init();


    // sleeping
//    set_sleep_mode(SLEEP_MODE_IDLE);
    modbus_rtu_driver__init();

//    sleep_enable();
    modbus_rtu_driver__start();
    temperature_reader__thread__start();
//    int1__start();

    display__render_packed(0); // ready

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
//    for(;;) {
//        if (modbus_rtu_driver__is_runnable()) {
//            modbus_rtu_driver__run();
//        }
//        else {
//            sei();
//            sleep_cpu();
//            cli();
//        }
//    }
    for(;;) {
        if (temperature_reader__thread__is_runnable())
            temperature_reader__thread__run();
    }
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}


#define SERVER__REGISTER__T                         (MODBUS_SERVER__INPUT_REGISTERS_START + 0)


#define SERVER__REGISTER__VALID_FRAMES_RECEIVED     (MODBUS_SERVER__HOLDING_REGISTERS_START + 0)
volatile uint16_t valid_frames_received;

#define SERVER__REGISTER__INVALID_FRAMES_RECEIVED   (MODBUS_SERVER__HOLDING_REGISTERS_START + 1)
volatile uint16_t invalid_frames_received;

#define SERVER__REGISTER__FRAMES_SENT               (MODBUS_SERVER__HOLDING_REGISTERS_START + 2)
volatile uint16_t frames_sent;

#define SERVER__REGISTER__PROTOCOL_ERRORS           (MODBUS_SERVER__HOLDING_REGISTERS_START + 3)
volatile uint16_t protocol_errors;

#define SERVER__REGISTER__BUFFER_OVERFLOWS          (MODBUS_SERVER__HOLDING_REGISTERS_START + 4)
volatile uint16_t buffer_overflows;

#define SERVER__REGISTER__PULSE_COUNTER             (MODBUS_SERVER__HOLDING_REGISTERS_START + 5)
volatile uint16_t pulse_counter;


void int1__run(void) {
    ++pulse_counter;
    display__render_packed(pulse_counter & 0xFF);
}

void modbus_server__on_valid_frame_received(void) {
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
    display__render_packed(0xfe);
    ++invalid_frames_received;
}

void modbus_rtu_driver__on_frame_sent(void) {
    ++frames_sent;
}

void modbus_rtu_driver__on_protocol_error(void) {
    display__render_packed(0xee);
    ++protocol_errors;
}

void modbus_rtu_driver__on_buffer_overflow(void) {
    display__render_packed(0xbe);
    ++buffer_overflows;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count) {
    display__render_packed(0x04);
    do {
        switch (register_address++) {
        case SERVER__REGISTER__T:
            buffer__put_u16(1);
            break;
        default:
            return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
        }
    }
    while (--register_count);
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_holding_registers(uint16_t register_address, uint16_t register_count) {
    display__render_packed(0x03);
    do {
        switch (register_address++) {
        case SERVER__REGISTER__VALID_FRAMES_RECEIVED:
            buffer__put_u16(valid_frames_received);
            break;
        case SERVER__REGISTER__INVALID_FRAMES_RECEIVED:
            buffer__put_u16(invalid_frames_received);
            break;
        case SERVER__REGISTER__FRAMES_SENT:
            buffer__put_u16(frames_sent);
            break;
        case SERVER__REGISTER__PROTOCOL_ERRORS:
            buffer__put_u16(protocol_errors);
            break;
        case SERVER__REGISTER__BUFFER_OVERFLOWS:
            buffer__put_u16(buffer_overflows);
            break;
        case SERVER__REGISTER__PULSE_COUNTER:
            buffer__put_u16(pulse_counter);
            break;
        default:
            return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
        }
    }
    while (--register_count);
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Handle writing of holding register.
 */
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value) {
    display__render_packed(0x06);
    switch (register_address) {
    case SERVER__REGISTER__VALID_FRAMES_RECEIVED:
        valid_frames_received = register_value;
        break;
    case SERVER__REGISTER__INVALID_FRAMES_RECEIVED:
        invalid_frames_received = register_value;
        break;
    case SERVER__REGISTER__FRAMES_SENT:
        frames_sent = register_value;
        break;
    case SERVER__REGISTER__PROTOCOL_ERRORS:
        protocol_errors = register_value;
        break;
    case SERVER__REGISTER__BUFFER_OVERFLOWS:
        buffer_overflows = register_value;
        break;
    case SERVER__REGISTER__PULSE_COUNTER:
        pulse_counter = register_value;
        break;
    default:
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
    }
    return MODBUS_EXCEPTION__NONE;
}
