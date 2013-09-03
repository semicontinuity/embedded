// =============================================================================
// Delay timer for handling of 1.5 and 3.5 character timeouts
// during USART data reception
// =============================================================================

#include "delay_timer.h"

#include "cpu/avr/timer1.h"
#include <avr/interrupt.h>
#include <stdint.h>


void delay_timer__init(void) {
    timer1__compare_a__value__set(DELAY_TIMER__T15_VALUE);
    timer1__compare_a__interrupt__enabled__set(1);

    timer1__compare_b__value__set(DELAY_TIMER__T35_VALUE);
    timer1__compare_b__interrupt__enabled__set(1);
}


void delay_timer__start(void) {
    timer1__value__set(0);
    timer1__switch_conf(TIMER1_CONF_DEFAULT, TIMER1_CONF_WGM_NORMAL | DELAY_TIMER__CONF);
}


void delay_timer__stop(void) {
    timer1__switch_conf(TIMER1_CONF_WGM_NORMAL | DELAY_TIMER__CONF, TIMER1_CONF_DEFAULT);
}


/**
 * 1.5 characters timeout expired
 */
ISR(timer1__compare_a__interrupt__VECTOR) {
    delay_timer__on_t15_expired();
}


/**
 * 3.5 characters timeout expired
 */
ISR(timer1__compare_b__interrupt__VECTOR) {
    delay_timer__on_t35_expired();
}