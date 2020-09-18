// =============================================================================
// Debounce timer for the keyboard,
// implemented with Timer 1 Compare A interrupt.
//
// Add the following definitions:
//
// timer1__comp_a__run = keyboard__debounce_timer__expired
// keyboard__debounce_timer__run = <handler function>
//
// <handler function> could be e.g. keyboard__reset_masks
// =============================================================================



#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer.h"
#include "cpu/avr/timer1.h"

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__init(void) {
    // NB: manages the whole timer
    timer1__switch_core_conf(
        KEYBOARD__DEBOUNCE_TIMER__CONF__INITIALIZED, KEYBOARD__DEBOUNCE_TIMER__CONF__STARTED
    );
    timer1__compare_a__interrupt__enabled__set(1);  // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__start(void) {
    timer1__compare_a__value__set(timer1__value__get() + KEYBOARD__DEBOUNCE_TIMER__DELAY);
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__debounce_timer__expired(void) {
    keyboard__debounce_timer__run();
}
