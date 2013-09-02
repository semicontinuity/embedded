// =============================================================================
// Delay timer
// =============================================================================

#ifndef DELAY_TIMER_H
#define DELAY_TIMER_H


#include <avr/interrupt.h>
#include <stdint.h>


void delay_timer__init(void);

void delay_timer__start(void);

void delay_timer__stop(void);

/** Callback to be implemented */
void delay_timer__on_t15_expired(void);

/** Callback to be implemented */
void delay_timer__on_t35_expired(void);

#endif