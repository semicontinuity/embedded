// =============================================================================
// Remote switch MODBUS server: counters and server callbacks.
// =============================================================================

#include "services/comm/modbus_server.h"

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include "drivers/out/debug_led_lcd_d7.h"
#include "drivers/out/debug_led_lcd_d6.h"
#include "drivers/out/debug_led_lcd_d5.h"
#include "drivers/out/debug_led_lcd_d4.h"

#include "services/temperature_reader.h"


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
}

void modbus_rtu_driver__on_char_buffered(void) {
}

void modbus_rtu_driver__on_buffer_overflow(void) {
    ++buffer_overflows;
}

void modbus_rtu_driver__on_char_timeout(void) {
}

void modbus_rtu_driver__on_char_format_error(void) {
    debug_led_lcd_d7__toggle();
}

void modbus_rtu_driver__on_char_lost(void) {
    debug_led_lcd_d6__toggle();
}

void modbus_rtu_driver__on_frame_timeout(void) {
}

void modbus_rtu_driver__on_frame_processing(void) {
}

void modbus_rtu_driver__on_response(void) {
}

void modbus_rtu_driver__on_no_response(void) {
}

void modbus_rtu_driver__on_protocol_error(void) {
    debug_led_lcd_d5__toggle();
    ++protocol_errors;
}

void modbus_rtu_driver__on_frame_sent(void) {
    ++frames_sent;
}

void modbus_server__on_valid_frame_received(void) {
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
    ++invalid_frames_received;
}


modbus_exception modbus_server__read_coils(void) {
    buffer__put_u8(
        (
            PORT_REG(OUT__LEDS__PORT) & (SIGNAL_MASK(OUT__LED1) | SIGNAL_MASK(OUT__LED2) | SIGNAL_MASK(OUT__LED3) | SIGNAL_MASK(OUT__LED4))
        ) >> OUT__LED1__PIN
    );
    return MODBUS_EXCEPTION__NONE;
}

modbus_exception modbus_server__write_single_coil(uint16_t address, uint8_t active) {
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

modbus_exception modbus_server__read_holding_registers(void) {
    buffer__put_u16(valid_frames_received);
    buffer__put_u16(invalid_frames_received);
    buffer__put_u16(frames_sent);
    buffer__put_u16(protocol_errors);
    buffer__put_u16(buffer_overflows);
    return MODBUS_EXCEPTION__NONE;
}

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
