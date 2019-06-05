// =============================================================================
// Debounce timer for the keyboard's port D,
// implemented with Timer 2 Compare B interrupt.
//
// Add the following definitions:
//
// timer2__comp_b__run = keyboard__port_d__debounce_timer__expired
// keyboard__port_d__debounce_timer__run = <handler function>
//
// <handler function> could be e.g. keyboard__port_d__mask__reset
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h"
#include "cpu/avr/timer2.h"

/**
 * Initialize debounce timer.
 */
void keyboard__port_d__debounce_timer__init(void) {
    // NB: manages the whole timer
    timer2__switch_core_conf(
        KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__INITIALIZED, KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__STARTED
    );
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__port_d__debounce_timer__start(void) {
    timer0__compare_d__value__set(timer2__value__get() + KEYBOARD__PORT_D__DEBOUNCE_TIMER__DELAY);
    timer0__compare_d__interrupt__enable();
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__port_d__debounce_timer__expired(void) {
    timer2__compare_d__interrupt__disable();
    keyboard__port_d__debounce_timer__run();
}
