#ifndef BUZZER_CONTROL__H
#define BUZZER_CONTROL__H

#include <stdbool.h>


void buzzer_controller__requested__set(bool requested);


// Must be invoked on every tick of fast timer (every1 ms)
void buzzer_controller__on_fast_timer_tick(void);

// Must be invoked every tick of slow timer, if controller is in RUNNING state
void buzzer_controller__on_slow_timer_tick(void);


#endif