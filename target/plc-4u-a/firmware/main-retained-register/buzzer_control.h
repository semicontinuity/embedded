#ifndef BUZZER_CONTROL__H
#define BUZZER_CONTROL__H

#include <stdbool.h>


// Must be invoked on every tick of fast timer (every1 ms)
void buzzer_controller__on_fast_timer_tick(void);

// Must be invoked every second
void buzzer_controller__run(void);


#endif