#ifndef __PWM_H
#define __PWM_H

#include "device.h"
#include <stdint.h>
#include "cpu/avr/timer0.h"


extern volatile uint8_t colors[8];


inline void pwm__init(void) {
    PWM_DIR |= _BV(PWM_0_PIN)|_BV(PWM_1_PIN)|_BV(PWM_2_PIN)|_BV(PWM_3_PIN)|_BV(PWM_4_PIN)|_BV(PWM_5_PIN);
}


inline void pwm__start(void) {
    timer0__overflow_interrupt_enable();
    timer0__start(TIMER0_MODE_RUN_NO_PRESCALER);
}


inline void pwm__stop(void) {
    timer0__stop();
    timer0__overflow_interrupt_disable();
}


#endif