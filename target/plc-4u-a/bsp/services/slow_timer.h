#ifndef SLOW_TIMER_H
#define SLOW_TIMER_H


void slow_timer__run(void);

/**
 * Invoked on every tick of the slow timer, every 250ms.
 * Implement.
 */
void slow_timer__do_run(void);


#endif
