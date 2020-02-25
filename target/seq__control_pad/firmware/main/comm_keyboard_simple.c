// =============================================================================
// On I2C Read request, responds with the 1-byte keyboard event, or 0 if none
// =============================================================================

#include "comm_events.h"

#include <avr/interrupt.h>
#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>

#include <drivers/out/led_a.h>


// keyboard callbacks
// -----------------------------------------------------------------------------

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-19)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    led_a__toggle();
    if (!comm_events__queue__is_full()) {
        comm_events__queue__put(
            IF_BIT_SET_CONST_A_ELSE_CONST_B(
                    state,
                    bit,
                    (uint8_t) COMM_EVENTS__BUTTONS__EVENT_DEPRESSED(button),
                    (uint8_t) COMM_EVENTS__BUTTONS__EVENT_PRESSED(button)
            )
        );
        return true;
    }
    return false;
}
