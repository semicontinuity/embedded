// =============================================================================
// Timer 0 driver
// Counts always from 0 to 255
// =============================================================================

#ifndef __CPU_AVR_TIMER0_H
#define __CPU_AVR_TIMER0_H

// Generic "Compare" callback for devices with at least 1 OC unit.
#ifdef timer0__comp__run
INLINE void timer0__comp__run(void);
#endif


#define TIMER0_MODE_STOPPED		(0)
#define TIMER0_MODE_RUN_NO_PRESCALER	(                        _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_8	(            _BV(CS01)            )
#define TIMER0_MODE_RUN_PRESCALER_64	(            _BV(CS01) | _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_256	(_BV(CS02)                        )
#define TIMER0_MODE_RUN_PRESCALER_1024	(_BV(CS02)             | _BV(CS00))
#define TIMER0_MODE_RUN_EXT_CLK_FALLING	(_BV(CS02) | _BV(CS01)            )
#define TIMER0_MODE_RUN_EXT_CLK_RISING	(_BV(CS02) | _BV(CS01) | _BV(CS00))


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
 || defined(__AVR_AT90USB82__)\
 || defined(__AVR_AT90USB162__)

#   include "cpu/avr/timer0__2oc.h"

#elif defined(__AVR_ATmega8__)\
 || defined(__AVR_AT90S2313__)

#   include "cpu/avr/timer0__0oc.h"

#elif defined(__AVR_ATmega16__)

#   include "cpu/avr/timer0__1oc.h"

#else

#   error "Unsupported MCU"

#endif


#endif