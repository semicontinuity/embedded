// =====================================================================================================================
// I/O matrix scanner thread timer, implemented with Timer 1 CTC Mode (uses Compare A value/interrupt).
//
// Add the following definitions (change as needed):
//
// io_matrix__scanner__thread__function                    = timer1__compare_a__interrupt__VECTOR
// io_matrix__scanner__thread__function_attrs              = __attribute__((signal)) ISR_NAKED
// io_matrix__scanner__thread__function_naked              = 1
// io_matrix__scanner__thread__yield_with_reti             = 1
// IO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED    = (TIMER1_CONF_DEFAULT)
// IO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED        = (TIMER1_CONF_WGM_CTC_USE_OCRA | TIMER1_CONF_PRESCALER_8)
// =====================================================================================================================

#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h"
#include <cpu/avr/timer1.h>

/**
 * Initialize the I/O matrix scanner thread timer.
 */
void io_matrix__scanner__thread__timer__init(void) {
    timer1__compare_a__interrupt__enabled__set(1);
}

/**
 * Start the I/O matrix scanner thread timer.
 */
void io_matrix__scanner__thread__timer__start(void) {
//    timer1__switch_core_conf(
//        IO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED, IO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED
//    );
}
