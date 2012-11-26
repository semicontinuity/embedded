// =============================================================================
// Buzzer driver.
// Implemented with Timer 0,
// that is programmed to toggle the buzzer 1000 times per second. (500 Hz sound)
// 
// For the CPU frequency 8 MHz:
// buzzer: 8000000/64/125 = 1000Hz
//
// For the CPU frequency 1 MHz:
// system_tick: 1000000/8/125 = 1000Hz
// =============================================================================

#ifndef __BUZZER_H
#define __BUZZER_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"

inline void buzzer__init(void) {
    USE_AS_OUTPUT(BUZZER);
    OUT_0(BUZZER);

    TCCR0A = (WGM01 << 1) | (WGM00 << 0);	// CTC mode (WGM02 must be 0 in TCCR0B)
    OCR0A = 125;				// Period: 125 cycles, then Compare A interrupt is triggered
    TIMSK0 = _BV(OCIE0A);
}


inline void buzzer__start(void) {
    TCCR0B = TIMER0_MODE_RUN_PRESCALER_64;
}


inline void buzzer__stop(void) {
    TCCR0B = TIMER0_MODE_STOPPED;
    OUT_0(BUZZER);
}

#endif