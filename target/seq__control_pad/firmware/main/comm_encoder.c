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
                COMM_EVENTS__ENCODER__ROTATION_EVENT_CLOCKWISE(encoder),
                COMM_EVENTS__ENCODER__ROTATION_EVENT_COUNTERCLOCKWISE(encoder)
            )
        );
        return true;
    }
    return false;
}
