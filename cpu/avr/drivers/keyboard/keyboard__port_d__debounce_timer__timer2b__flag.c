// =============================================================================
// Debounce timer for the keyboard's port D,
// implemented with Timer 0 Compare B channel.
// The idea is that Interrupt flag is set by timer,
// when the specified timeout has elapsed,
// so it it easy to check the flag and proceed with keyboard handling.
// When the debounce period is started,
// the Interrupt flag is cleared,
// to indicate that keyboard handling must be skipped.
//
// Add the following definitions:
//
// KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__INITIALIZED
// KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__STARTED
// KEYBOARD__PORT_D__DEBOUNCE_TIMER__DELAY
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h"
#include "cpu/avr/timer2.h"

/**
 * Initializes the debounce timer.
 */
void keyboard__port_D__debounce_timer__init(void) {
    // NB: changes the state of the timer
    // It is assumed, that both channels are used for the same purpose (debouncing),
    // so it does not matter, that timer is started two times
    timer2__switch_basic_conf(
        KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__INITIALIZED, KEYBOARD__PORT_D__DEBOUNCE_TIMER__CONF__STARTED
    );
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__port_d__debounce_timer__start(void) {
    timer2__compare_b__value__set(timer2__value__get() + KEYBOARD__PORT_D__DEBOUNCE_TIMER__DELAY);
    timer2__compare_b__interrupt__pending__clear();
}

bool keyboard__port_d__debounce_timer__is_started(void) {
    // if there is no pending interrupt, it means, that debounce timer is still started (timeout has not elapsed)
    return !timer2__compare_b__interrupt__pending__get();
}
