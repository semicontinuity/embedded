#ifndef UPTIME_COUNTER_H
#define UPTIME_COUNTER_H


void uptime_counter__run(void);

/**
 * Invoked on every tick of the slow timer, every 250ms.
 * Implement.
 */
void slow_timer__do_run(void);


#endif
