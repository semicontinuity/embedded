// =============================================================================
// Seconds timer.
// Divides the output of the system timer to get 1 Hz frequency.
// =============================================================================

#ifndef __SERVICES__SECONDS_TIMER_H
#define __SERVICES__SECONDS_TIMER_H

#include <stdint.h>

extern uint8_t seconds_timer__value;

/* Callback function prototype, must be defined by the application code */ 
INLINE void seconds_timer__out__run(void);

/**
 * Called every system tick to generate 1 Hz clock.
 */
inline static void seconds_timer__run(void) {
    if (--seconds_timer__value == 0) {
        seconds_timer__value = SYSTEM_TIMER__FREQUENCY;
        seconds_timer__out__run();
    }
}


#endif