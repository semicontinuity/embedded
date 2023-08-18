#ifndef CONTACTOR_CONTROLLER__H
#define CONTACTOR_CONTROLLER__H


#include <stdbool.h>


void contactor_controller__on_slow_timer_tick(void);

void contactor_controller__actual_state_renderer__run(void);


#endif