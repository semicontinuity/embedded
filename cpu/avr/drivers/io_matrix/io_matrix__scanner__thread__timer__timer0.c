// =====================================================================================================================
// I/O matrix scanner thread timer, implemented with Timer 0.
//
// Add the following definitions:
//
// io_matrix__scanner__thread__function                    = timer0__overflow__interrupt__VECTOR
// io_matrix__scanner__thread__function_attrs              = __attribute__((signal)) ISR_NAKED
// io_matrix__scanner__thread__function_naked              = 1
// io_matrix__scanner__thread__yield_with_reti             = 1
// IO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED    = (TIMER0_CONF_DEFAULT)
// IO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED        = (TIMER0_CONF_PRESCALER_8)
// =====================================================================================================================

#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h"
#include "cpu/avr/timer0.h"

/**
 * Initialize the I/O matrix scanner thread timer.
 */
void io_matrix__scanner__thread__timer__init(void) {
    timer0__overflow__interrupt__enable();
}

/**
 * Start the I/O matrix scanner thread timer.
 */
void io_matrix__scanner__thread__timer__start(void) {
    timer0__switch_core_conf(
        IO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED, IO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED
    );
}
