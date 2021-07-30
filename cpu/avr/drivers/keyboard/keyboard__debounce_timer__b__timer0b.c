// =============================================================================
// Debounce timer B,
// implemented with Timer 0 Compare B interrupt.
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__b.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__b__init(void) {
    // NB: manages the whole timer
    timer0__switch_core_conf(
        KEYBOARD__DEBOUNCE_TIMER__A__CONF__INITIALIZED, KEYBOARD__DEBOUNCE_TIMER__A__CONF__STARTED
    );
    timer0__compare_b__interrupt__enable(); // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__b__start(void) {
    timer0__compare_b__value__set(timer0__value__get() + KEYBOARD__DEBOUNCE_TIMER__B__DELAY);
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__debounce_timer__b__expired(void) {
    keyboard__debounce_timer__b__run();
}
