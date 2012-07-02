#ifndef __CPU_AVR_TIMER0_M8_H
#define __CPU_AVR_TIMER0_M8_H

#include <avr/io.h>


#define timer0__overflow_interrupt_enable() do {\
    TIMSK  |= _BV(TOIE0); 	/* enable interrupts on timer 0 overflow */ \
} while(0)

#define timer0__overflow_interrupt_disable() do {\
    TIMSK  &= ~_BV(TOIE0); 	/* disable interrupts on timer 0 overflow */ \
} while(0)


#define timer0__start(mode) do {\
    TCCR0 = mode;	/* start timer in the user-defined mode  */\
} while(0)

#define timer0__stop() do {\
    TCCR0 = TIMER0_MODE_STOPPED; /* stop timer 0 */\
} while(0)


#endif