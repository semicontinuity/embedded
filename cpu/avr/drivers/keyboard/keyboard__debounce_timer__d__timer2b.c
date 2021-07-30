// =============================================================================
// Debounce timer D,
// implemented with Timer 2 Compare B interrupt.
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__d.h"
#include "cpu/avr/timer2.h"

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__d__init(void) {
    // NB: manages the whole timer
    timer2__switch_basic_conf(
        KEYBOARD__DEBOUNCE_TIMER__D__CONF__INITIALIZED, KEYBOARD__DEBOUNCE_TIMER__D__CONF__STARTED
    );
    timer2__compare_b__interrupt__enable(); // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__d__start(void) {
    timer2__compare_b__value__set(timer2__value__get() + KEYBOARD__DEBOUNCE_TIMER__D__DELAY);
}
