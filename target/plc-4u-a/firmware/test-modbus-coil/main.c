// =============================================================================
// Test MODBUS coil.
// The board has 1 coil attached to on-board LED.
// The goal is to get/set the coil via MODBUS.
// =============================================================================

#include "drivers/out/led_alarm.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include <avr/interrupt.h>


void modbus_rtu_driver__on_char_received(void) {
}

void modbus_rtu_driver__on_char_buffered(void) {
}

void modbus_rtu_driver__on_buffer_overflow(void) {
}

void modbus_rtu_driver__on_char_timeout(void) {
}

void modbus_rtu_driver__on_char_format_error(void) {
}

void modbus_rtu_driver__on_char_lost(void) {
}

void modbus_rtu_driver__on_frame_timeout(void) {
}

void modbus_rtu_driver__on_frame_processing(void) {
}

void modbus_rtu_driver__on_response(void) {
}

void modbus_rtu_driver__on_no_response(void) {
}

void modbus_rtu_driver__on_frame_sent(void) {
}

void modbus_rtu_driver__on_protocol_error(void) {
}

void modbus_server__on_valid_frame_received(void) {
}

void modbus_server__on_invalid_frame_received(void) {
}

// =============================================================================

/**
 * Process READ COILS request.
 * Reads all coils at once!
 * Buffer write pointer: after BYTE COUNT field (already written), ready to write bytes with coil bits.
 * Write exactly MODBUS_SERVER__COIL_COUNT bits to the buffer.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_coils(void) {
     __asm__ __volatile__( "modbus_server__read_coils:");
    uint8_t byte0 = 0;
    if (led_alarm__is_set()) byte0 |= _BV(0);
     __asm__ __volatile__( "modbus_server__read_coils_1:");
    buffer__put_u8(byte0);
    return MODBUS_EXCEPTION__NONE;
}

// =============================================================================

/**
 * Handle reading of input registers.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count) {
    __asm__ __volatile__( "modbus_server__read_input_registers:");
    return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
}


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__read_holding_registers(uint16_t register_address, uint16_t register_count) {
    __asm__ __volatile__( "modbus_server__read_holding_registers:");
    return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
}

// =============================================================================


/**
 * Process WRITE SINGLE COIL request.
 * Buffer: do not read or write.
 */
modbus_exception modbus_server__write_single_coil(uint16_t address, uint8_t active) {
    __asm__ __volatile__( "modbus_server__write_single_coil:");
    if (address == 0) {
        led_alarm__set(active);
    }
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Handle writing of holding register.
 */
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value) {
    __asm__ __volatile__( "modbus_server__write_holding_register:");
    return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;
}


// =============================================================================
// Application
// =============================================================================


static void application__init(void) {
    led_alarm__init();
    modbus_rtu_driver__configure(USART0_DIVISOR(4800L));
}

static void application__start(void) {
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
    __asm__ __volatile__( "main__loop:");
    for(;;) {
        __asm__ __volatile__( "main__modbus_rtu_driver:");
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
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
