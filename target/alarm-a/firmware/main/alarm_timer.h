/**
 * One-shot timer.
 */
#ifndef __ALARM_TIMER_H
#define __ALARM_TIMER_H

#include <stdint.h>

extern uint8_t alarm_timer__counter;

#define alarm_timer__set(t) do { alarm_timer__counter=(t); } while(0)
#define alarm_timer__reset() do { alarm_timer__counter = 0; } while(0)

// callback
void alarm_timer__output__run(void);

static inline void alarm_timer__run(void) {
    // state transition after certain timeout only
    if (alarm_timer__counter == 0) return;
    if (--alarm_timer__counter == 0) {
        alarm_timer__output__run();
    }
}


#endif