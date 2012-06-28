#ifndef __MX8__TIMER2_H
#define __MX8__TIMER2_H

#include <avr/io.h>


// There are the following 8 modes:
//
#define TIMER2_MODE_STOPPED		(0)
#define TIMER2_MODE_RUN_NO_PRESCALER	(                        _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_8	(            _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_32	(            _BV(CS21) | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_64	(_BV(CS22)                        )
#define TIMER2_MODE_RUN_PRESCALER_128	(_BV(CS22)             | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_256	(_BV(CS22) | _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_1024	(_BV(CS22) | _BV(CS21) | _BV(CS20))


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