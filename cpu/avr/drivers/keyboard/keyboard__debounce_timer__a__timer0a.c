// =============================================================================
// Debounce timer A,
// implemented with Timer 0 Compare A interrupt.
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__a.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__a__init(void) {
    // NB: manages the whole timer
    timer0__switch_core_conf(
        KEYBOARD__DEBOUNCE_TIMER__A__CONF__INITIALIZED, KEYBOARD__DEBOUNCE_TIMER__A__CONF__STARTED
    );
    timer0__compare_a__interrupt__enable(); // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__a__start(void) {
    timer0__compare_a__value__set(timer0__value__get() + KEYBOARD__DEBOUNCE_TIMER__A__DELAY);
}
