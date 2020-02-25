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
            COMM_EVENTS__ENCODER__ROTATION_EVENT(encoder, delta)
        );
        return true;
    }
    return false;
}

/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder0__handle_switch_event(uint8_t encoder, uint8_t new_state, uint8_t bit) {
    led_a__toggle();
    if (!comm_events__queue__is_full()) {
        comm_events__queue__put(
            IF_BIT_SET_CONST_A_ELSE_CONST_B(
                new_state, bit,
                COMM_EVENTS__ENCODER__SWITCH_EVENT_DEPRESSED(encoder),
                COMM_EVENTS__ENCODER__SWITCH_EVENT_PRESSED(encoder)
            )
        );
        return true;
    }
    return false;
}
