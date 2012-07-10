#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <avr/pgmspace.h>

extern uint8_t counter;

void process_periodic_event(void);
void process_scheduled_event(void);

#define callback_in(t) do { counter=(t); } while(0)
#define cancel_callback() do { counter=0; } while(0)

#endif
    