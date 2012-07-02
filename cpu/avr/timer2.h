#ifndef __CPU_AVR_TIMER2_H
#define __CPU_AVR_TIMER2_H


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



#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 

#   include "cpu/avr/timer2__mx8.h"

#elif defined(__AVR_ATmega8__)

#   include "cpu/avr/timer2__m8.h"

#else
    #error "Unsupported MCU"
#endif


#endif