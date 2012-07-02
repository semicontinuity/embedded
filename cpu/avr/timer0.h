#ifndef __CPU_AVR_TIMER0_H
#define __CPU_AVR_TIMER0_H


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



#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 

#   include "cpu/avr/timer0__mx8.h"

#elif defined(__AVR_ATmega8__)

#   include "cpu/avr/timer0__m8.h"

#else
    #error "Unsupported MCU"
#endif


#endif