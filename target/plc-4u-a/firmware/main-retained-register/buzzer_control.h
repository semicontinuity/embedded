#ifndef BUZZER_CONTROL__H
#define BUZZER_CONTROL__H

#include <stdbool.h>


bool buzzer_controller__is_requested(void);
bool buzzer_controller__is_running(void);


// Must be invoked on every tick of fast timer (every1 ms)
void buzzer_controller__on_fast_timer_tick(void);


// Request buzzer start; to be invoked in STOPPED state
void buzzer_controller__start(void);

// Must be invoked every tick of slow timer, if controller is in RUNNING state
void buzzer_controller__run(void);

// Request buzzer stop; to be invoked in RUNNING state
void buzzer_controller__stop(void);


#endif