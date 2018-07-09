// =============================================================================
// Remote switch (without LCD)
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include "drivers/out/debug_led_lcd_d7.h"
#include "drivers/out/debug_led_lcd_d6.h"
#include "drivers/out/debug_led_lcd_d5.h"
#include "drivers/out/debug_led_lcd_d4.h"

#include "drivers/comm/onewire__bus.h"
#include "drivers/comm/onewire.h"

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include "services/temperature_reader.h"
#include "services/buttons_handler.h"

#include <avr/interrupt.h>


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

void modbus_rtu_driver__on_char_format_error(void) {
    debug_led_lcd_d7__set(1);
}

void modbus_rtu_driver__on_char_lost(void) {
    debug_led_lcd_d6__set(1);
}

void modbus_rtu_driver__on_frame_timeout(void) {
//    led2__set(1);
}

void modbus_rtu_driver__on_frame_processing(void) {
    TOGGLE(MODBUS_RTU_DRIVER__FRAME_PROCESSING__LED);
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
    debug_led_lcd_d5__set(1);
    ++protocol_errors;
}

void modbus_server__on_valid_frame_received(void) {
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
    debug_led_lcd_d4__set(1);
    ++invalid_frames_received;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_coils(void) {
     __asm__ __volatile__( "modbus_server__read_coils:");
    buffer__put_u8(
        (
            PORT_REG(OUT__LEDS__PORT) & (SIGNAL_MASK(OUT__LED1) | SIGNAL_MASK(OUT__LED2) | SIGNAL_MASK(OUT__LED3) | SIGNAL_MASK(OUT__LED4))
        ) >> OUT__LED1__PIN
    );
    return MODBUS_EXCEPTION__NONE;
}



/**
 * Handle writing of single coil (output LEDs/relays).
 */
modbus_exception modbus_server__write_single_coil(uint16_t address, uint8_t active) {
    __asm__ __volatile__( "modbus_server__write_single_coil:");
    if (address == 0) {
        led1__set(active);
    }
    else if (--address == 0) {
        led2__set(active);
    }
    else if (--address == 0) {
        led3__set(active);
    }
    else {
        led4__set(active);
    }
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count) {
    __asm__ __volatile__( "modbus_server__read_input_registers:");
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
    __asm__ __volatile__( "modbus_server__read_holding_registers:");
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
    __asm__ __volatile__( "modbus_server__write_holding_register:");
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


void temperature_reader__reading__on_changed(void) {
}

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__FRAME_PROCESSING__LED);
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__USART_RX__ENABLED__LED);
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__FRAME_RECEIVED__LED);
    USE_AS_OUTPUT(ONEWIRE__THREAD__ALIVE__LED);

    led1__init();
    led2__init();
    led3__init();
    led4__init();

    debug_led_lcd_d7__init();
    debug_led_lcd_d6__init();
    debug_led_lcd_d5__init();
    debug_led_lcd_d4__init();

    buttons_handler__init();

    modbus_rtu_driver__init();

    onewire__bus__init();
    onewire__thread__init();
    temperature_reader__thread__start();
}

static void application__start(void) {
    buttons_handler__start();
    modbus_rtu_driver__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
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
    __asm__ __volatile__( "main__loop:");
    for(;;) {
        __asm__ __volatile__( "main__modbus_rtu_driver:");
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
        __asm__ __volatile__( "main__temperature_reader__thread:");
        if (temperature_reader__thread__is_runnable()) {
            temperature_reader__thread__run();
        }
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
