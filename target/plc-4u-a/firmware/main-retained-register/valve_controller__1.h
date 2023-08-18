#ifndef VALVE_CONTROL__1__H
#define VALVE_CONTROL__1__H

#include <stdbool.h>


void valve_controller__1__close(void);


bool valve_controller__1__is_runnable(void);
void valve_controller__1__run(void);


bool valve_controller__1__limit_switches_state_renderer__is_runnable(void);
void valve_controller__1__limit_switches_state_renderer__run(void);


#endif