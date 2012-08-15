// =============================================================================
// The driver for 2 buttons at pins BUTTON1 and BUTTON2,
// all on the same BUTTONS__PORT.
// Does not support concurrent button presses.
// =============================================================================
#include "buttons.h"
#include <stdint.h>
#include <avr/io.h>
#include "cpu/avr/gpio.h"


#define BUTTONS_MASK (_BV(BUTTON1__PIN) | _BV(BUTTON2__PIN))

uint8_t buttons__state = BUTTONS_MASK;
uint8_t buttons__changed;


inline void button1__init(void) {
    USE_AS_INPUT(BUTTON1);
    ENABLE_PULLUP(BUTTON1);
}

inline void button2__init(void) {
    USE_AS_INPUT(BUTTON2);
    ENABLE_PULLUP(BUTTON2);
}

INLINE void buttons__init(void) {
    button1__init();
    button2__init();
}

/**
 * Called periodically to scan buttons
 */
INLINE void buttons__run(void) {
    uint8_t current_state = PORT_VALUE(BUTTONS) & BUTTONS_MASK;
    if ((buttons__changed = buttons__state ^ current_state)) {
        buttons__state = current_state;

        if (buttons__changed & _BV(BUTTON1__PIN)) {
            buttons__on_button1_changed();
        }
        if (buttons__changed & _BV(BUTTON2__PIN)) {
            buttons__on_button2_changed();
        }
    }
}
