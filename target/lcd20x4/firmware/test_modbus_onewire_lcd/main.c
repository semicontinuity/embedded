// =============================================================================
// Test MODBUS communications
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"
#include "LCD.h"         
#include "prototip_fun.h"

#include "drivers/comm/onewire__bus.h"
#include "services/temperature_reader.h"

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include <avr/interrupt.h>
#include <avr/pgmspace.h>


uint16_t as_two_hex_chars(const uint8_t value) {
    uint8_t hn = (value >> 4);
    uint8_t hc = hn + (hn < 10 ? '0' : ('A' - 10));
    uint8_t ln = (value & 0x0F);
    uint8_t lc = ln + (ln < 10 ? '0' : ('A' - 10));
    return (hc<<8) | lc;
}


void display__print_frame(void) {
    LCDGotoXY(0, 0);

    uint8_t l = buffer__limit__get();
    uint8_t* p = buffer__data;
    for (;;) {
       if (l == 0) break;

       uint8_t value = *p++;
       uint16_t l_chars = as_two_hex_chars(value);
       LCDdata(l_chars >> 8);
       LCDdata(l_chars & 0xFF);

       --l;
    }
    LCDdata('=');
}


void modbus_rtu_driver__on_frame_processing(void) {
    led1__toggle();
    display__print_frame();
}

void modbus_rtu_driver__on_char_received(void) {
}

void modbus_rtu_driver__on_char_buffered(void) {
}

void modbus_rtu_driver__on_frame_timeout(void) {
}


void modbus_rtu_driver__on_char_timeout(void) {
}

void modbus_rtu_driver__on_response(void) {
    led3__set(1);
}

void modbus_rtu_driver__on_no_response(void) {
    led3__set(0);
}



void temperature_reader__reading__on_changed(void) {
}

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    led1__init();
    led2__init();
    led3__init();

    init();
    LCDstring_of_flash(PSTR("MODBUS test"), 0, 0);

//    onewire__bus__init();
    modbus_rtu_driver__init();

//    temperature_reader__thread__start();
    modbus_rtu_driver__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
//        if (temperature_reader__thread__is_runnable()) {
//            temperature_reader__thread__run();
//        }
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


void modbus_server__on_valid_frame_received(void) {
    led2__set(1);
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
    led2__set(0);
    ++invalid_frames_received;
}

void modbus_rtu_driver__on_frame_sent(void) {
    ++frames_sent;
}

void modbus_rtu_driver__on_protocol_error(void) {
    ++protocol_errors;
}

void modbus_rtu_driver__on_buffer_overflow(void) {
    ++buffer_overflows;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count) {
    do {
        switch (register_address++) {
        case SERVER__REGISTER__T:
            buffer__put_u16(temperature_reader__reading);
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
