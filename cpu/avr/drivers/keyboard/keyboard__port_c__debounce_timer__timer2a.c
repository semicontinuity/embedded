// =============================================================================
// Debounce timer for the keyboard's port C,
// implemented with Timer 2 Compare A interrupt.
//
// Add the following definitions:
//
// timer2__comp_a__run = keyboard__port_c__debounce_timer__expired
// keyboard__port_c__debounce_timer__run = <handler function>
//
// <handler function> could be e.g. keyboard__port_c__mask__reset
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h"
#include "cpu/avr/timer2.h"

/**
 * Initialize debounce timer.
 */
void keyboard__port_c__debounce_timer__init(void) {
    // NB: manages the whole timer
    timer2__switch_basic_conf(
        KEYBOARD__PORT_C__DEBOUNCE_TIMER__CONF__INITIALIZED, KEYBOARD__PORT_C__DEBOUNCE_TIMER__CONF__STARTED
    );
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__port_c__debounce_timer__start(void) {
    timer2__compare_a__value__set(timer2__value__get() + KEYBOARD__PORT_C__DEBOUNCE_TIMER__DELAY);
    timer2__compare_a__interrupt__enable();
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__port_c__debounce_timer__expired(void) {
    timer2__compare_a__interrupt__disable();
    keyboard__port_c__debounce_timer__run();
}
