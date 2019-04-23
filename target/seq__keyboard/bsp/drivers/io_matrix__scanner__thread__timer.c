// =============================================================================
// I/O matrix scanner thread timer
// =============================================================================


#include "drivers/io_matrix__scanner__thread__timer.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize the timer.
 */
void io_matrix__scanner__thread__timer__init(void) {
    timer0__overflow__interrupt__enable();
}

/**
 * Start the timer.
 */
void io_matrix__scanner__thread__timer__start(void) {
    timer0__switch_core_conf(IO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED, IO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED);
}
