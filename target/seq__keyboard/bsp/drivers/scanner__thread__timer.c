// =============================================================================
// Scanner thread timer
// =============================================================================


#include "drivers/scanner__thread__timer.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize the timer.
 */
void scanner__thread__timer__init(void) {
    timer0__overflow__interrupt__enable();
}

/**
 * Start the timer.
 */
void scanner__thread__timer__start(void) {
    timer0__switch_core_conf(SCANNER__THREAD__TIMER__CONF__INITIALIZED, SCANNER__THREAD__TIMER__TIMER__CONF__STARTED);
}
