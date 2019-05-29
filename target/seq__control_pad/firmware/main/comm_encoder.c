// =====================================================================================================================
// Implements encoder callbacks by enqueuing corresponding events in the event queue, that is read by I2C Reads
// =====================================================================================================================

#include "drivers/in/encoder0.h"
#include "comm_events.h"

#include <avr/interrupt.h>
#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>

#include <drivers/out/led_a.h>


// encoder callbacks
// -----------------------------------------------------------------------------

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder0__handle_rotation_event(uint8_t encoder, uint8_t delta) {
    led_a__toggle();
    if (!comm_events__queue__is_full()) {
        comm_events__queue__put(
            IF_BIT_SET_CONST_A_ELSE_CONST_B(
                delta, 7,
                comm_events__encoder_rotation_event_counterclockwise(encoder),
                comm_events__encoder_rotation_event_clockwise(encoder)
            )
        );
        return true;
    }
    return false;
}
