// =============================================================================
// One-shot timer for use with alarm service.
// =============================================================================
#ifndef __SERVICES__ALARM__TIMER_H
#define __SERVICES__ALARM__TIMER_H

#include <stdint.h>

extern uint8_t alarm__timer__counter;


inline static void alarm__timer__set(const uint8_t t) {
    alarm__timer__counter = t;
}


// Alarm timer callback - to be implemented by user
void alarm__timer__output__run(void);


static inline void alarm__timer__run(void) {
    if (alarm__timer__counter == 0) return;
    if (--alarm__timer__counter == 0) {
        alarm__timer__output__run();
    }
}


#endif