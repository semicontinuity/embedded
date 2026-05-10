// =============================================================================
// System timer.
// Implemented with Timer 0, overflow interrupt.
// =============================================================================


#ifndef __SERVICES__SYSTEM_TIMER_H
#define __SERVICES__SYSTEM_TIMER_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/timer0.h"


#define SYSTEM_TIMER__CONF__DEFAULT     (TIMER0_CONF_DEFAULT)
#define SYSTEM_TIMER__CONF__INITIALIZED (TIMER0_CONF_STOPPED)
#define SYSTEM_TIMER__CONF__STARTED     (SYSTEM_TIMER__CONF)


inline static void system_timer__init(void) {
    if (SYSTEM_TIMER__CONF__DEFAULT != SYSTEM_TIMER__CONF__INITIALIZED)
        timer0__switch_conf(SYSTEM_TIMER__CONF__DEFAULT, SYSTEM_TIMER__CONF__INITIALIZED);
}


inline static void system_timer__start(void) {
    timer0__overflow__interrupt__enable();
    timer0__switch_conf(SYSTEM_TIMER__CONF__INITIALIZED, SYSTEM_TIMER__CONF__STARTED);
}


inline static void system_timer__stop(void) {
    timer0__switch_conf(SYSTEM_TIMER__CONF__STARTED, SYSTEM_TIMER__CONF__INITIALIZED);
    timer0__overflow__interrupt__disable();
}

#endif
