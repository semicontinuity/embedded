// =============================================================================
// USI USART timer.
// Implemented with Timer 0,
// =============================================================================


#ifndef __USI_USART__TIMER_H
#define __USI_USART__TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


#define USI_USART__TIMER__COMPARE_VALUE     (52)
#define USI_USART__TIMER__CONF__DEFAULT     (TIMER0_CONF_DEFAULT)
#define USI_USART__TIMER__CONF__INITIALIZED (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(USI_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_OCRB(26) | TIMER0_CONF_STOPPED)
#define USI_USART__TIMER__CONF__STARTED     (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(USI_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_OCRB(26) | TIMER0_CONF_PRESCALER_8)


inline static void usi_usart__timer__init(void) {
    timer0__switch_conf(USI_USART__TIMER__CONF__DEFAULT, USI_USART__TIMER__CONF__INITIALIZED);
}


inline static void usi_usart__timer__start(void) {
    //timer0__compare_b__interrupt__enable();
    timer0__switch_conf(USI_USART__TIMER__CONF__INITIALIZED, USI_USART__TIMER__CONF__STARTED);
}


inline static void usi_usart__timer__stop(void) {
    //timer0__compare_b__interrupt__disable();
    timer0__switch_conf(USI_USART__TIMER__CONF__STARTED, USI_USART__TIMER__CONF__INITIALIZED);
}

#endif