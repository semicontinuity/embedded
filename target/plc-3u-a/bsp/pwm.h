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
    timer0__overflow__interrupt__enable();
    timer0__switch_conf(TIMER0_CONF_DEFAULT, TIMER0_CONF_NO_PRESCALER);
}


inline void pwm__stop(void) {
    timer0__switch_conf(TIMER0_CONF_NO_PRESCALER, TIMER0_CONF_DEFAULT);
    timer0__overflow__interrupt__disable();
}


#endif