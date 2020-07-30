// =============================================================================
// Soft USART timer.
// Implemented with Timer 0.
// =============================================================================


#ifndef __SOFT_USART__TIMER_H
#define __SOFT_USART__TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


#define SOFT_USART__TIMER__COMPARE_VALUE     (F_CPU/SOFT_USART__BAUD_RATE/8)
#define SOFT_USART__TIMER__CONF__DEFAULT     (TIMER0_CONF_DEFAULT)
#define SOFT_USART__TIMER__CONF__INITIALIZED (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(SOFT_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_STOPPED)
#define SOFT_USART__TIMER__CONF__STARTED     (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(SOFT_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_PRESCALER_8)


void soft_usart__timer__init(void) {
    timer0__switch_conf(SOFT_USART__TIMER__CONF__DEFAULT, SOFT_USART__TIMER__CONF__INITIALIZED);
}


void soft_usart__timer__start(void) {
    timer0__compare_a__interrupt__enable();
    timer0__switch_conf(SOFT_USART__TIMER__CONF__INITIALIZED, SOFT_USART__TIMER__CONF__STARTED);
}


void soft_usart__timer__stop(void) {
    timer0__compare_a__interrupt__disable();
    timer0__switch_conf(SOFT_USART__TIMER__CONF__STARTED, SOFT_USART__TIMER__CONF__INITIALIZED);
}

#endif