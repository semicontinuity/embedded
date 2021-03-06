// =============================================================================
// Debounce timer for the keyboard's port B,
// implemented with Timer 0 Compare B interrupt.
//
// Add the following definitions:
//
// timer0__comp_b__run = keyboard__port_b__debounce_timer__expired
// keyboard__port_b__debounce_timer__run = <handler function>
//
// <handler function> could be e.g. keyboard__port_b__mask__reset
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize debounce timer.
 */
void keyboard__port_b__debounce_timer__init(void) {
    // NB: manages the whole timer
    timer0__switch_core_conf(
        KEYBOARD__PORT_B__DEBOUNCE_TIMER__CONF__INITIALIZED, KEYBOARD__PORT_B__DEBOUNCE_TIMER__CONF__STARTED
    );
    timer0__compare_b__interrupt__enable(); // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__port_b__debounce_timer__start(void) {
    timer0__compare_b__value__set(timer0__value__get() + KEYBOARD__PORT_B__DEBOUNCE_TIMER__DELAY);
//    timer0__compare_b__interrupt__enable();
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__port_b__debounce_timer__expired(void) {
//    timer0__compare_b__interrupt__disable();
    keyboard__port_b__debounce_timer__run();
}
