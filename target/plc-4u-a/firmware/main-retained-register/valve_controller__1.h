#ifndef VALVE_CONTROL__1__H
#define VALVE_CONTROL__1__H

#include <stdbool.h>
#include <stdint.h>


void valve_controller__1__close(void);

void valve_controller__1__on_minutes_timer_tick(void);

void valve_controller__1__on_slow_timer_tick(void);


bool valve_controller__1__limit_switch__failure__get(void);

uint16_t valve_controller__1__idle_time_minutes__get(void);


#endif