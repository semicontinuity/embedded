// =============================================================================
// Test valve state rendering.
// Discrete input F state is copied to discrete output F.
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
#include <drivers/in/digital_inputs.h>

#include "services/discrete_inputs.h"
#include "services/discrete_outputs.h"
#include "drivers/out/digital_outputs.h"
#include "drivers/fast_timer.h"
#include "valve_controller.h"


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
    buffer__put_u8(discrete_inputs__byte0);
    buffer__put_u8(discrete_inputs__byte1);
    __asm__ __volatile__( "modbus_server__read_discrete_inputs__done:");
    return MODBUS_EXCEPTION__NONE;
}


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
    buffer__put_u8(discrete_outputs__byte0);
    buffer__put_u8(discrete_outputs__byte1);
    __asm__ __volatile__( "modbus_server__read_coils__done:");
    return MODBUS_EXCEPTION__NONE;
}

// =============================================================================
// Fast timer callback
// =============================================================================

void fast_timer__do_run(void) {
    discrete_inputs__run();
    valve_controller__run();
    discrete_outputs__run();
}

// =============================================================================
// Application
// =============================================================================


static void application__init(void) {
    digital_inputs__init();
    digital_outputs__init();

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
    for (;;) {
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
