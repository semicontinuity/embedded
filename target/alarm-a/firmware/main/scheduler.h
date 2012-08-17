#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <avr/pgmspace.h>

void system_timer__on_system_tick(void);
void system_timer__on_second_tick(void);

#endif
    