#ifndef __CPU_AVR_TIMER2_MX8_H
#define __CPU_AVR_TIMER2_MX8_H

#include <avr/io.h>


#define timer2__overflow_interrupt_enable() do {\
    TIMSK2  |= _BV(TOIE2); 	/* enable interrupts on timer 0 overflow */ \
} while(0)

#define timer2__overflow_interrupt_disable() do {\
    TIMSK2  &= ~_BV(TOIE2); 	/* disable interrupts on timer 0 overflow */ \
} while(0)


#define timer2__start(mode) do {\
    TCCR2B = mode;	/* start timer in the user-defined mode  */\
} while(0)


#define timer2__stop() do {\
    TCCR2B = TIMER2_MODE_STOPPED;					\
} while(0)


#endif