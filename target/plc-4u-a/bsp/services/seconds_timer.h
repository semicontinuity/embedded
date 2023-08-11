#ifndef SECONDS_TIMER_H
#define SECONDS_TIMER_H


/** Must be invoked on every tick of the slow timer, every 250ms */
void seconds_timer__run(void);

/**
 * Invoked on every tick of the seconds timer, every second.
 * Implement.
 */
void seconds_timer__do_run(void);


#endif
