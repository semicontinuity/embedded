#ifndef BUZZER_CONTROL__H
#define BUZZER_CONTROL__H

#include <stdbool.h>


void buzzer_controller__requested__set(bool requested);


// Must be invoked every tick of slow timer, if controller is in RUNNING state
void buzzer_controller__on_slow_timer_tick(void);

void buzzer_controller__init(void);


#endif