// =============================================================================
// Soft USART timer.
// Implemented with Timer 2,
// that is programmed to overflow about 2400 times per second,
// to communicate at 2400 baud.
// 
// For the CPU frequency 20 MHz, prescaler 32:
// 20000000/32/256 = 2441.4 baud, 1.73% faster (software correction possible).
// =============================================================================


#ifndef __SOFT_USART__TIMER_H
#define __SOFT_USART__TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer2.h"


#define SOFT_USART__TIMER__CONF__DEFAULT     (TIMER2_CONF_DEFAULT)
#define SOFT_USART__TIMER__CONF__INITIALIZED (TIMER2_CONF_WGM_NORMAL | TIMER2_CONF_STOPPED)
#define SOFT_USART__TIMER__CONF__STARTED     (TIMER2_CONF_WGM_NORMAL | TIMER2_CONF_PRESCALER_32)


inline static void soft_usart__timer__init(void) {
    timer2__switch_basic_conf(SOFT_USART__TIMER__CONF__DEFAULT, SOFT_USART__TIMER__CONF__INITIALIZED);
}

inline static void soft_usart__timer__start(void) {
    timer2__switch_basic_conf(SOFT_USART__TIMER__CONF__INITIALIZED, SOFT_USART__TIMER__CONF__STARTED);
}

inline static void soft_usart__timer__stop(void) {
    timer2__switch_basic_conf(SOFT_USART__TIMER__CONF__STARTED, SOFT_USART__TIMER__CONF__INITIALIZED);
}

inline static void soft_usart__timer__rx__start(void) {
    timer2__compare_a__value__set(timer2__value__get() + 128);  // first match at the middle of the start bit
    timer2__compare_a__interrupt__enable();
}

inline static void soft_usart__timer__rx__stop(void) {
    timer2__compare_a__interrupt__disable();
}

inline static void soft_usart__timer__tx__start(void) {
    timer2__compare_b__value__set(timer2__value__get());  // first match at the end of start bit, 1 period from now
    timer2__compare_b__interrupt__enable();
}

inline static void soft_usart__timer__tx__stop(void) {
    timer2__compare_b__interrupt__disable();
}

#endif