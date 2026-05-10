/*
 * System timer.
 * Uses TIMER0 overflow interrupt.
 * CS=100, CLKio/256
 * Interrupt will be invoked F_CPU/256/256 times per second
 */
#ifndef __SYSTEM_TIMER_H
#define __SYSTEM_TIMER_H


static inline void system_timer__init(void) {
    TIMSK0 = _BV (TOIE0);
}


static inline void system_timer__start(void) {
    TCCR0B = _BV (CS02);
}


void system_timer__on_system_tick(void);
void system_timer__on_second_tick(void);


#endif
    