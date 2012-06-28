#ifndef __MX8__TIMER0_H
#define __MX8__TIMER0_H

#include <avr/io.h>


// Timer 0 counts always from 0 to 255
// There are the following 8 modes:
//
#define TIMER0_MODE_STOPPED		(0)
#define TIMER0_MODE_RUN_NO_PRESCALER	(                        _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_8	(            _BV(CS01)            )
#define TIMER0_MODE_RUN_PRESCALER_64	(            _BV(CS01) | _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_256	(_BV(CS02)                        )
#define TIMER0_MODE_RUN_PRESCALER_1024	(_BV(CS02)             | _BV(CS00))
#define TIMER0_MODE_RUN_EXT_CLK_FALLING	(_BV(CS02) | _BV(CS01)            )
#define TIMER0_MODE_RUN_EXT_CLK_RISING	(_BV(CS02) | _BV(CS01) | _BV(CS00))


#define timer0__overflow_interrupt_enable() do {\
    TIMSK0  |= _BV(TOIE0); 	/* enable interrupts on timer 0 overflow */ \
} while(0)

#define timer0__overflow_interrupt_disable() do {\
    TIMSK0  &= ~_BV(TOIE0); 	/* disable interrupts on timer 0 overflow */ \
} while(0)


#define timer0__start(mode) do {\
    TCCR0B = mode;	/* start timer in the user-defined mode  */\
} while(0)

#define timer0_stop() do {\
    TCCR0B = TIMER0_MODE_STOPPED; /* stop timer 0 */\
} while(0)


#endif