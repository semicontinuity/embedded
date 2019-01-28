// =============================================================================
// Soft USART timer.
// Implemented with Timer 0,
// that is programmed to generate interrupts per every bit at 2400 baud.
// 
// For the CPU frequency 1 MHz:
// 1000000/2400 = 416.6 cycles
// For prescaler 8: compare value = 416.6/8 ~= 52, delay after start bit = 78
// 1000000 / 8 / 52 = 2404 baud.
// =============================================================================


#ifndef __SOFT_USART__TIMER_H
#define __SOFT_USART__TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


#define SOFT_USART__TIMER__COMPARE_VALUE     (52)
#define SOFT_USART__TIMER__CONF__DEFAULT     (TIMER0_CONF_DEFAULT)
#define SOFT_USART__TIMER__CONF__INITIALIZED (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(SOFT_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_STOPPED)
#define SOFT_USART__TIMER__CONF__STARTED     (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(SOFT_USART__TIMER__COMPARE_VALUE) | TIMER0_CONF_PRESCALER_8)

INLINE void soft_usart__tx__thread__run(void);


inline static void soft_usart__timer__init(void) {
    timer0__switch_conf(SOFT_USART__TIMER__CONF__DEFAULT, SOFT_USART__TIMER__CONF__INITIALIZED);
}

inline static void soft_usart__timer__reset(void) {
    timer0__value__set(256 - 78 + 52); // Compare A will be triggered in 1.5 bit time from now
}


inline static void soft_usart__timer__start(void) {
    timer0__compare_a__interrupt__enable();
    timer0__switch_conf(SOFT_USART__TIMER__CONF__INITIALIZED, SOFT_USART__TIMER__CONF__STARTED);
}


inline static void soft_usart__timer__stop(void) {
    timer0__compare_a__interrupt__disable();
    timer0__switch_conf(SOFT_USART__TIMER__CONF__STARTED, SOFT_USART__TIMER__CONF__INITIALIZED);
}

#endif