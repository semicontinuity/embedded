#ifndef __PWM_H
#define __PWM_H

#include <stdint.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


extern volatile uint8_t colors[8];


inline void pwm__init(void) {
    USE_PORT_AS_OUTPUT(PWM);
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