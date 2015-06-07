// =============================================================================
// 16-bit Timer 1 driver
// =============================================================================

#ifndef __CPU_AVR_TIMER1_H
#define __CPU_AVR_TIMER1_H

#include <stdint.h>
#include <avr/io.h>

#ifdef timer1__comp_a__run
INLINE void timer1__comp_a__run(void);
#endif

#ifdef timer1__comp_b__run
INLINE void timer1__comp_b__run(void);
#endif

#ifdef timer1__comp_c__run
INLINE void timer1__comp_c__run(void);
#endif


// Values for prescaler (bits 0..3 in TCCR1B)
#define TIMER1_MODE_STOPPED		(0)
#define TIMER1_MODE_RUN_NO_PRESCALER	(                        _BV(CS10))
#define TIMER1_MODE_RUN_PRESCALER_8	(            _BV(CS11)            )
#define TIMER1_MODE_RUN_PRESCALER_32	(            _BV(CS11) | _BV(CS10))
#define TIMER1_MODE_RUN_PRESCALER_64	(_BV(CS12)                        )
#define TIMER1_MODE_RUN_PRESCALER_128	(_BV(CS12)             | _BV(CS10))
#define TIMER1_MODE_RUN_PRESCALER_256	(_BV(CS12) | _BV(CS11)            )
#define TIMER1_MODE_RUN_PRESCALER_1024	(_BV(CS12) | _BV(CS11) | _BV(CS10))


#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega48A__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega88A__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega88PA__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega168A__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_AT90S8535__)\
 || defined(__AVR_ATmega16__)\
 || defined(__AVR_ATmega8__)\
 || defined(__AVR_ATmega8535__)\
 || defined(__AVR_AT90USB82__)\
 || defined(__AVR_AT90USB162__)\
 || defined(__AVR_AT90S2313__)

#   include "cpu/avr/timer1__2oc.h"

#else

#   error "Unsupported MCU"

#endif


#endif