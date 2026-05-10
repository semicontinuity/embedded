// =============================================================================
// One-shot timer for use with alarm service.
// =============================================================================
#ifndef __SERVICES__WATER_LEAK_HANDLER__TIMER_H
#define __SERVICES__WATER_LEAK_HANDLER__TIMER_H

#include <stdint.h>

extern uint8_t water_leak_handler__timer__counter;


inline static void water_leak_handler__timer__set(const uint8_t t) {
    water_leak_handler__timer__counter = t;
}


// Alarm timer callback - to be implemented by user
INLINE void water_leak_handler__timer__output__run(void);


static inline void water_leak_handler__timer__run(void) {
    if (water_leak_handler__timer__counter == 0) return;
    if (--water_leak_handler__timer__counter == 0) {
        water_leak_handler__timer__output__run();
    }
}


#endif