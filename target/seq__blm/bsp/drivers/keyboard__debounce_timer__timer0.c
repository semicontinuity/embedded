// =============================================================================
// Debounce timer for the keyboard.
// Invoke keyboard__debounce_timer__start() after any button event.
// When the timer expires, keyboard__debounce_timer__run() callback
// will be invoked and the timer stops until next call to start().
// =============================================================================


#include "drivers/keyboard__debounce_timer.h"
#include "cpu/avr/timer0.h"

#define SYSTEM_TIMER__CONF__INITIALIZED (TIMER0_CONF_DEFAULT)
#define SYSTEM_TIMER__CONF__STARTED     (TIMER0_CONF_PRESCALER_1024)


/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__init(void) {
    timer0__overflow__interrupt__enable();
}

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__start(void) {
    timer0__value__set(0);  // re-start if timer is running
    timer0__switch_core_conf(SYSTEM_TIMER__CONF__INITIALIZED, SYSTEM_TIMER__CONF__STARTED);
}

void keyboard__debounce_timer__expired(void) {
    timer0__switch_core_conf(SYSTEM_TIMER__CONF__STARTED, SYSTEM_TIMER__CONF__INITIALIZED);
    keyboard__debounce_timer__run();
}
