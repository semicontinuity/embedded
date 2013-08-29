#ifndef __PWM_H
#define __PWM_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"
#include <stdint.h>


extern volatile uint8_t colors[6];


#define TIMER0_CONF_STOP (TIMER0_CONF_WGM_NORMAL | TIMER0_CONF_OC0A_CLEAR | TIMER0_CONF_OCRA(128) | TIMER0_CONF_STOPPED)
#define TIMER0_CONF_RUN  (TIMER0_CONF_WGM_NORMAL | TIMER0_CONF_OC0A_CLEAR | TIMER0_CONF_OCRA(128) | TIMER0_CONF_PRESCALER_8) 


inline void pwm__init(void) {
    USE_AS_OUTPUT(LED_R);
    USE_AS_OUTPUT(LED_G);
    USE_AS_OUTPUT(LED_B);

    timer0__switch_conf(TIMER0_CONF_DEFAULT, TIMER0_CONF_STOP);
}


inline void pwm__start(void) {
    timer0__compare_a__interrupt__enable();
    timer0__switch_conf(TIMER0_CONF_STOP, TIMER0_CONF_RUN);
}



inline void pwm__stop(void) {
    timer0__switch_conf(TIMER0_CONF_RUN, TIMER0_CONF_STOP);
    timer0__compare_a__interrupt__disable();
}


#endif