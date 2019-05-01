// =============================================================================
// Debounce timer for the keyboard, implemented with Timer 2.
// Add the following define:
// timer2__overflow__run=keyboard__debounce_timer__expired
//
// Invoke keyboard__debounce_timer__start() after any button event.
// When the timer expires, keyboard__debounce_timer__run() callback
// will be invoked and the timer stops until next call to start().
// =============================================================================


#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer.h"
#include "cpu/avr/timer2.h"

#define DEBOUNCE_TIMER__CONF__INITIALIZED (TIMER2_CONF_DEFAULT)
#define DEBOUNCE_TIMER__CONF__STARTED     (TIMER2_CONF_PRESCALER_1024)


/**
 * Initializes debounce timer.
 */
void keyboard__debounce_timer__init(void) {
    timer2__overflow__interrupt__enable();
}

/**
 * Starts (or re-starts) debounce timer.
 */
void keyboard__debounce_timer__start(void) {
    timer2__value__set(0);  // re-start if timer is running
    timer2__switch_basic_conf(DEBOUNCE_TIMER__CONF__INITIALIZED, DEBOUNCE_TIMER__CONF__STARTED);
}

void keyboard__debounce_timer__expired(void) {
    timer2__switch_basic_conf(DEBOUNCE_TIMER__CONF__STARTED, DEBOUNCE_TIMER__CONF__INITIALIZED);
    keyboard__debounce_timer__run();
}
