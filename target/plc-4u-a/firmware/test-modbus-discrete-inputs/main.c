// =============================================================================
// Test MODBUS READ DISCRETE INPUTS function.
// =============================================================================

#include "drivers/in/buttons.h"
#include "drivers/in/extra_inputs.h"
#include "drivers/in/valve_limit_switches.h"
#include "drivers/in/water_leak_sensors.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include <avr/interrupt.h>

#include "fast_timer.h"


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
 * Process READ DISCRETE INPUTS request.
 * Reads all discrete inputs at once!
 * Buffer write pointer: after BYTE COUNT field (already written), ready to write bytes with input bits.
 * Write exactly MODBUS_SERVER__DISCRETE_INPUTS_COUNT bits to the buffer.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_discrete_inputs(void) {
     __asm__ __volatile__( "modbus_server__read_discrete_inputs:");

    uint8_t byte0;
    LOAD_CONST8(byte0, 0);
    if (water_leak_sensor__a__is_on()) byte0 |= _BV(0);
    if (water_leak_sensor__b__is_on()) byte0 |= _BV(1);
    if (water_leak_sensor__c__is_on()) byte0 |= _BV(2);
    if (water_leak_sensor__d__is_on()) byte0 |= _BV(3);
    if (valve_limit_switch__a__is_on()) byte0 |= _BV(4);
    if (valve_limit_switch__b__is_on()) byte0 |= _BV(5);
    if (valve_limit_switch__c__is_on()) byte0 |= _BV(6);
    if (valve_limit_switch__d__is_on()) byte0 |= _BV(7);
    buffer__put_u8(byte0);

    uint8_t byte1;
    LOAD_CONST8(byte1, 0);
    if (extra_input__a__is_on()) byte1 |= _BV(0);
    if (extra_input__b__is_on()) byte1 |= _BV(1);
    if (button__a__is_on()) byte1 |= _BV(2);
    if (button__b__is_on()) byte1 |= _BV(3);
    if (button__c__is_on()) byte1 |= _BV(4);
    if (button__d__is_on()) byte1 |= _BV(5);
    if (button__e__is_on()) byte1 |= _BV(6);
    if (button__f__is_on()) byte1 |= _BV(7);
    buffer__put_u8(byte1);

     __asm__ __volatile__( "modbus_server__read_discrete_inputs__done:");
    return MODBUS_EXCEPTION__NONE;
}


// =============================================================================
// Application
// =============================================================================


static void application__init(void) {
    water_leak_sensor__a__init();
    water_leak_sensor__b__init();
    water_leak_sensor__c__init();
    water_leak_sensor__d__init();

    valve_limit_switch__a__init();
    valve_limit_switch__b__init();
    valve_limit_switch__c__init();
    valve_limit_switch__d__init();

    extra_input__a__init();
    extra_input__b__init();

    button__a__init();
    button__b__init();
    button__c__init();
    button__d__init();
    button__e__init();
    button__f__init();

    fast_timer__init();

    modbus_rtu_driver__configure(USART0_DIVISOR(4800L));
}

static void application__start(void) {
    fast_timer__start();
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
        if (fast_timer__is_runnable()) {
            fast_timer__run();
        }
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
