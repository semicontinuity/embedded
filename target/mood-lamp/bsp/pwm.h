#ifndef __PWM_H
#define __PWM_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"
#include <stdint.h>


extern volatile uint8_t colors[6];


inline void pwm__init(void) {
    USE_AS_OUTPUT(LED_R);
    USE_AS_OUTPUT(LED_G);
    USE_AS_OUTPUT(LED_B);

    OCR0A = 128;
    TCCR0A = 0x02;
}


inline void pwm__start(void) {
    timer0__compare_a__interrupt_enable();
    timer0__start(TIMER0_MODE_RUN_PRESCALER_8);
}



inline void pwm__stop(void) {
    timer0__stop();
    timer0__compare_a__interrupt_disable();
}


#endif