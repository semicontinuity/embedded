// =============================================================================
// Sample MODBUS server.
// =============================================================================


#include "buffer.h"
#include "modbus_rtu_driver.h"
#include "modbus_server.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>


// main
// -----------------------------------------------------------------------------

int main(void) {
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    modbus_rtu_driver__init();

    sleep_enable();
    modbus_rtu_driver__start();

    for(;;) {
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
        else {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}


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


void modbus_server__on_valid_frame_received(void) {
    ++valid_frames_received;
}

void modbus_server__on_invalid_frame_received(void) {
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
        }
    }
    while (--register_count);
    return MODBUS_EXCEPTION__NONE;

}


/**
 * Handle writing of holding register.
 */
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value) {
    switch (register_address++) {
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
    }
    return MODBUS_EXCEPTION__NONE;
}
