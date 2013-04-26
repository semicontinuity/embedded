// =============================================================================
// System timer.
// Implemented with Timer 0,
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


#ifndef __DRIVERS__SYSTEM_TIMER_H
#define __DRIVERS__SYSTEM_TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


#define SYSTEM_TIMER__CONF__DEFAULT     (TIMER0_CONF_DEFAULT)
#define SYSTEM_TIMER__CONF__INITIALIZED (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(125) | TIMER0_CONF_STOPPED)
#define SYSTEM_TIMER__CONF__STARTED     (TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(125) | TIMER0_CONF_PRESCALER_256)

/* Callback function prototype, must be defined by the application code */ 
INLINE void system_timer__out__run(void);


inline static void system_timer__init(void) {
    timer0__switch_conf(SYSTEM_TIMER__CONF__DEFAULT, SYSTEM_TIMER__CONF__INITIALIZED);
}


inline static void system_timer__start(void) {
    timer0__ctc__interrupt__enable();
    timer0__switch_conf(SYSTEM_TIMER__CONF__INITIALIZED, SYSTEM_TIMER__CONF__STARTED);
}


inline static void system_timer__stop(void) {
    timer0__ctc__interrupt__disable();
    timer0__switch_conf(SYSTEM_TIMER__CONF__STARTED, SYSTEM_TIMER__CONF__INITIALIZED);
}

#endif