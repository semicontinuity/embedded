// =============================================================================
// Debounce timer C,
// implemented with Timer 2 Compare A interrupt.
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__c.h"
#include "cpu/avr/timer2.h"

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__c__init(void) {
    // NB: manages the whole timer
    timer2__switch_basic_conf(
        KEYBOARD__DEBOUNCE_TIMER__C__CONF__INITIALIZED, KEYBOARD__DEBOUNCE_TIMER__C__CONF__STARTED
    );
    timer2__compare_a__interrupt__enable(); // interrupt will fire regularly
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__c__start(void) {
    timer2__compare_a__value__set(timer2__value__get() + KEYBOARD__DEBOUNCE_TIMER__C__DELAY);
}

/**
 * Invoked, when the programmed debounce delay has elapsed.
 */
void keyboard__debounce_timer__c__expired(void) {
    keyboard__debounce_timer__c__run();
}
