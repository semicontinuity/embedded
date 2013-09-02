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


#endif