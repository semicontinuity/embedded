// =============================================================================
// Timer 2 driver
// =============================================================================

#ifndef __CPU_AVR_TIMER2_H
#define __CPU_AVR_TIMER2_H



#define TIMER2_MODE_STOPPED		(0)
#define TIMER2_MODE_RUN_NO_PRESCALER	(                        _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_8	(            _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_32	(            _BV(CS21) | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_64	(_BV(CS22)                        )
#define TIMER2_MODE_RUN_PRESCALER_128	(_BV(CS22)             | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_256	(_BV(CS22) | _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_1024	(_BV(CS22) | _BV(CS21) | _BV(CS20))


#define TIMER2_CONF_STOPPED		                (0)
#define TIMER2_CONF_NO_PRESCALER	                (                        _BV(CS20))
#define TIMER2_CONF_PRESCALER_8                         (            _BV(CS21)            )
#define TIMER2_CONF_PRESCALER_32	                (            _BV(CS21) | _BV(CS20))
#define TIMER2_CONF_PRESCALER_64	                (_BV(CS22)                        )
#define TIMER2_CONF_PRESCALER_128                       (_BV(CS22)             | _BV(CS20))
#define TIMER2_CONF_PRESCALER_256	                (_BV(CS22) | _BV(CS21)            )
#define TIMER2_CONF_PRESCALER_1024                      (_BV(CS22) | _BV(CS21) | _BV(CS20))

#define TIMER2_CONF_DEFAULT                             (0)



#ifdef timer2__comp__run

#ifndef timer2__comp__run__attrs
#  define timer2__comp__run__attrs
#endif

INLINE void timer2__comp__run(void) timer2__comp__run__attrs;

#endif



#ifdef timer2__comp_a__run

#ifndef OCR2A
#  error "Timer 2 does not have Compare A channel"
#endif
#ifndef timer2__comp_a__run__attrs
#define timer2__comp_a__run__attrs
#endif

INLINE void timer2__comp_a__run(void) timer2__comp_a__run__attrs;

#endif



#ifdef timer2__comp_b__run

#ifndef OCR2B
#  error "Timer 2 does not have Compare A channel"
#endif
#ifndef timer2__comp_b__run__attrs
#define timer2__comp_b__run__attrs
#endif

INLINE void timer2__comp_b__run(void) timer2__comp_b__run__attrs;

#endif



static inline void timer2__value__set(const uint8_t value) {
    TCNT2 = value;
}

static inline uint8_t timer2__value__get(void) {
    return TCNT2;
}



#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega48A__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega88A__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega88PA__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega168A__)\
 || defined(__AVR_ATmega168P__)

#  define TIMER2_REG_B          (TCCR2B)
#  define TIMER2_REG_MASK       (TIMSK2)
#  define timer2__compare_a__interrupt__VECTOR          TIMER2_COMPA_vect
#  define timer2__compare_b__interrupt__VECTOR          TIMER2_COMPA_vect
#  include "cpu/avr/timer2__2oc.h"

#elif defined(__AVR_AT90S8535__)\
 || defined(__AVR_ATmega16__)\
 || defined(__AVR_ATmega8__)\
 || defined(__AVR_ATmega8535__)\
 || defined(__AVR_AT90S2313__)

#  define TIMER2_REG_B          (TCCR2)
#  define TIMER2_REG_MASK       (TIMSK)
#  define timer2__compare_a__interrupt__VECTOR          TIMER2_COMP_vect
#  include "cpu/avr/timer2__1oc.h"

#else
#  error "Unsupported MCU"
#endif


#endif