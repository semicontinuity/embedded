// =============================================================================
// System timer.
// =============================================================================


#ifndef __SYSTEM_TIMER_H
#define __SYSTEM_TIMER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
//#include "cpu/avr/timer0.h"


inline void system_timer__init(void) {
}

// 1. enable TIMER0_OVF_vect
// 2. no Force Output Compare, WGMxx=NORMAL, Normal operation, OC0 disconnected, f=clkIO/1024
inline void system_timer__start(void) {
    TIMSK = _BV (TOIE0);
    TCCR0 = _BV (CS02) | _BV(CS00);
}


INLINE void system_timer__on_system_tick(void);

#endif