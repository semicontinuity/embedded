#ifndef FAST_TIMER_H
#define FAST_TIMER_H


void fast_timer__init(void);

void fast_timer__start(void);

bool fast_timer__is_runnable(void);

void fast_timer__run(void);


#endif
