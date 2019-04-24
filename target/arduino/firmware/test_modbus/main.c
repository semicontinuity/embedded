// =============================================================================
// Modbus test
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "buffer.h"
#include "modbus_rtu_driver.h"
#include "modbus_server.h"

#include <avr/interrupt.h>
#include <util/delay.h>



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


void modbus_rtu_driver__on_char_received(void) {
//    led1__set(1);
}

void modbus_rtu_driver__on_char_buffered(void) {
//    led2__set(1);
}

void modbus_rtu_driver__on_buffer_overflow(void) {
//    led3__set(1);
    ++buffer_overflows;
}

void modbus_rtu_driver__on_char_timeout(void) {
//    led1__set(1);
}

void modbus_rtu_driver__on_frame_timeout(void) {
//    led2__set(1);
}

void modbus_rtu_driver__on_frame_processing(void) {
//    led3__set(1);
}

void modbus_rtu_driver__on_response(void) {
//    led2__set(1);
}

void modbus_rtu_driver__on_no_response(void) {
//    led3__set(1);
}

void modbus_rtu_driver__on_frame_sent(void) {
    ++frames_sent;
}

void modbus_rtu_driver__on_protocol_error(void) {
    ++protocol_errors;
}

void modbus_server__on_valid_frame_received(void) {
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
    ++invalid_frames_received;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_coils(void) {
    buffer__put_u8((PORT_REG(OUT__LEDS__PORT) & (SIGNAL_MASK(OUT__LED1) | SIGNAL_MASK(OUT__LED2) | SIGNAL_MASK(OUT__LED3))) >> OUT__LED1__PIN);
    return MODBUS_EXCEPTION__NONE;
}




/**
 * Handle writing of single coil (output LEDs/relays).
 */

modbus_exception modbus_server__write_single_coil(uint16_t address, uint8_t active) {
    if (address == 0) {
        led1__set(active);
    }
    else if (--address == 0) {
        led2__set(active);
    }
    else {
        led3__set(active);
    }
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count) {
    do {
        switch (register_address++) {
        case SERVER__REGISTER__T:
            buffer__put_u16(0xAA55);
//            buffer__put_u16(temperature_reader__reading);
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
    default:
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
    }
    return MODBUS_EXCEPTION__NONE;
}


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    led1__init();
    led2__init();
    led3__init();
    modbus_rtu_driver__init();
}

static void application__start(void) {
    modbus_rtu_driver__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();

    led1__set(1);
    led2__set(1);
    led3__set(1);
    _delay_ms(500);
    led1__set(0);
    led2__set(0);
    led3__set(0);
    _delay_ms(100);

    application__start();
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
