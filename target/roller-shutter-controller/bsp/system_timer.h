// =============================================================================
// System timer.
// Implemented with Timer 2,
// that is programmed to generate system ticks 250 times per second.
// 
// For the CPU frequency 8 MHz:
// system_tick: 8000000/256/125 = 250Hz
//
// For the CPU frequency 1 MHz:
// system_tick: 1000000/32/125 = 250Hz
//
// Then, the following frequencies are generated in software:
// second_tick:      250/250 = 1Hz
// ten_seconds_tick: 1/10 = 1 per 10 seconds
// =============================================================================


#ifndef __SYSTEM_TIMER_H
#define __SYSTEM_TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer2.h"


INLINE void system_timer__on_system_tick(void);


inline void system_timer__init(void) {
    TCCR2A = (WGM21 << 1) | (WGM20 << 0);	// CTC mode (WGM22 must be 0 in TCCR2B)
    OCR2A = 125;				// Period: 125 cycles, then Compare A interrupt is triggered
}


inline void system_timer__start(void) {
    TIMSK2 |= _BV(OCIE2A);
    TCCR2B = TIMER2_MODE_RUN_PRESCALER_256;
}


inline void system_timer__stop(void) {
    TIMSK2 &= ~_BV(OCIE2A);
    TCCR2B = TIMER2_MODE_STOPPED;
}


inline void system_timer__loop(void) {
    for(;;);
}

#endif