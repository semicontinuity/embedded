// =============================================================================
// Timer 2 driver
// =============================================================================

#ifndef __CPU_AVR_TIMER2_H
#define __CPU_AVR_TIMER2_H

#include <stdint.h>
#include <avr/io.h>


#define TIMER2_MODE_STOPPED		(0)
#define TIMER2_MODE_RUN_NO_PRESCALER	(                        _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_8	(            _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_32	(            _BV(CS21) | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_64	(_BV(CS22)                        )
#define TIMER2_MODE_RUN_PRESCALER_128	(_BV(CS22)             | _BV(CS20))
#define TIMER2_MODE_RUN_PRESCALER_256	(_BV(CS22) | _BV(CS21)            )
#define TIMER2_MODE_RUN_PRESCALER_1024	(_BV(CS22) | _BV(CS21) | _BV(CS20))



#ifdef timer2__comp_a__run

#ifndef timer2__comp_a__run__attrs
#define timer2__comp_a__run__attrs
#endif

INLINE void timer2__comp_a__run(void) timer2__comp_a__run__attrs;

#endif



#ifdef timer2__comp_b__run

#ifndef OCR2B
#  error "Timer 2 does not have Compare B channel"
#endif
#ifndef timer2__comp_b__run__attrs
#define timer2__comp_b__run__attrs
#endif

INLINE void timer2__comp_b__run(void) timer2__comp_b__run__attrs;

#endif


#if defined(TIMER2__COMPARE_UNITS)
#  error "Must not define TIMER2__COMPARE_UNITS"
#endif

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


#  define TIMER2__COMPARE_UNITS	                        2
#  define TIMER2_REG_B                                  (TCCR2B)
#  define TIMER2_REG_MASK                               (TIMSK2)
#  define TIMER2_REG_VALUE                              (TCNT2)
#  define TIMER2__COMPARE_A__INTERRUPT__ENABLE__HOST    (TIMER2_REG_MASK)
#  define TIMER2__COMPARE_A__INTERRUPT__ENABLE__BIT     (OCIE2A)
#  define timer2__compare_a__interrupt__VECTOR          TIMER2_COMPA_vect
#  define TIMER2__COMPARE_B__INTERRUPT__ENABLE__HOST    (TIMER2_REG_MASK)
#  define TIMER2__COMPARE_B__INTERRUPT__ENABLE__BIT     (OCIE2B)
#  define timer2__compare_b__interrupt__VECTOR          TIMER2_COMPB_vect



#elif defined(__AVR_AT90S8535__)\
 || defined(__AVR_ATmega16__)\
 || defined(__AVR_ATmega8__)\
 || defined(__AVR_ATmega8535__)\
 || defined(__AVR_AT90S2313__)


#  define TIMER2__COMPARE_UNITS	                        1
#  define TIMER2__OVERFLOW__INTERRUPT__ENABLE__HOST     (TIMSK)
#  define TIMER2__OVERFLOW__INTERRUPT__ENABLE__BIT      (TOIE2)
#  define TIMER2__OVERFLOW__INTERRUPT__PENDING__HOST    (TIFR)
#  define TIMER2__OVERFLOW__INTERRUPT__PENDING__BIT     (TOV2)
#  define timer2__compare_a__interrupt__VECTOR          TIMER2_COMP_vect
#  define TIMER2__COMPARE_A__INTERRUPT__ENABLE__HOST    (TIMSK)
#  define TIMER2__COMPARE_A__INTERRUPT__ENABLE__BIT     (OCIE2)
#  define TIMER2__COMPARE_A__INTERRUPT__PENDING__HOST   (TIFR)
#  define TIMER2__COMPARE_A__INTERRUPT__PENDING__BIT    (OCF2)

#  define TIMER2_REG_B                                  (TCCR2)
#  define TIMER2_REG_MASK                               (TIMSK)
#  define TIMER2_REG_VALUE                              (TCNT2)


#else
#  error "Unsupported MCU"
#endif


#  define timer2__overflow__interrupt__VECTOR          TIMER2_OVF_vect


static inline void timer2__value__set(const uint8_t value) {
    TIMER2_REG_VALUE = value;
}

static inline uint8_t timer2__value__get(void) {
    return TIMER2_REG_VALUE;
}


#if defined(TIMER2__OVERFLOW__INTERRUPT__ENABLE__HOST) && defined(TIMER2__OVERFLOW__INTERRUPT__ENABLE__BIT)

inline static void timer2__overflow__interrupt__enable(void) {
    TIMER2__OVERFLOW__INTERRUPT__ENABLE__HOST |= _BV(TIMER2__OVERFLOW__INTERRUPT__ENABLE__BIT);
}

inline static void timer2__overflow__interrupt__disable(void) {
    TIMER2__OVERFLOW__INTERRUPT__ENABLE__HOST &= ~_BV(TIMER2__OVERFLOW__INTERRUPT__ENABLE__BIT);
}

inline static void timer2__overflow__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) timer2__overflow__interrupt__enable(); else timer2__overflow__interrupt__disable();
}

#endif


#if defined(TIMER2__OVERFLOW__INTERRUPT__PENDING__HOST) && defined(TIMER2__OVERFLOW__INTERRUPT__PENDING__BIT)

inline static char timer2__compare_a__interrupt__pending__get(void) {
    return TIMER2__OVERFLOW__INTERRUPT__PENDING__HOST & _BV(TIMER2__OVERFLOW__INTERRUPT__PENDING__BIT);
}

inline static void timer2__compare_a__interrupt__pending__clear(void) {
    TIMER2__OVERFLOW__INTERRUPT__PENDING__HOST |= _BV(TIMER2__OVERFLOW__INTERRUPT__PENDING__BIT);
}

#endif


inline static void timer2__compare_a__interrupt__enable(void) {
    TIMER2_REG_MASK |= _BV(TIMER2__COMPARE_A__INTERRUPT__ENABLE__BIT);
}

inline static void timer2__compare_a__interrupt__disable(void) {
    TIMER2_REG_MASK &= ~_BV(TIMER2__COMPARE_A__INTERRUPT__ENABLE__BIT);
}

inline static void timer2__compare_a__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) timer2__compare_a__interrupt__enable(); else timer2__compare_a__interrupt__disable();
}


inline static void timer2__ctc__interrupt__enable(void) {
    timer2__compare_a__interrupt__enable();
}

inline static void timer2__ctc__interrupt__disable(void) {
    timer2__compare_a__interrupt__disable();
}



#if TIMER2__COMPARE_UNITS==1
#  include "cpu/avr/timer2__1oc.h"
#elif TIMER2__COMPARE_UNITS==2
#  include "cpu/avr/timer2__2oc.h"
#endif



#if TIMER2__COMPARE_UNITS > 0

#if defined(TIMER2__PERIOD) && !defined(TIMER2__CONF__INITIALIZED)
#  if TIMER2__PERIOD <= 0
#    error "Invalid period setting for Timer 2"
#  elif TIMER2__PERIOD <= 256
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD) - 1))
#  elif TIMER2__PERIOD <= 256*8
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/8) - 1))
#  elif TIMER2__PERIOD <= 256*32
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/32) - 1))
#  elif TIMER2__PERIOD <= 256*64
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/64) - 1))
#  elif TIMER2__PERIOD <= 256*128
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/128) - 1))
#  elif TIMER2__PERIOD <= 256*256
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/256) - 1))
#  elif TIMER2__PERIOD <= 256*1024
#    define TIMER2__CONF__INITIALIZED  (TIMER2_CONF_STOPPED | TIMER2_CONF_TOP((TIMER2__PERIOD/1024) - 1))
#  else
#    error "Period setting for Timer 2 is out of range"
#  endif
#endif

#if defined(TIMER2__PERIOD) && !defined(TIMER2__CONF__STARTED)
#  if TIMER2__PERIOD <= 0
#    error "Invalid period setting for Timer 2"
#  elif TIMER2__PERIOD <= 256
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_NO_PRESCALER | TIMER2_CONF_TOP((TIMER2__PERIOD) - 1))
#  elif TIMER2__PERIOD <= 256*8
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_8 | TIMER2_CONF_TOP((TIMER2__PERIOD/8) - 1))
#  elif TIMER2__PERIOD <= 256*32
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_32 | TIMER2_CONF_TOP((TIMER2__PERIOD/32) - 1))
#  elif TIMER2__PERIOD <= 256*64
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_64 | TIMER2_CONF_TOP((TIMER2__PERIOD/64) - 1))
#  elif TIMER2__PERIOD <= 256*128
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_128 | TIMER2_CONF_TOP((TIMER2__PERIOD/128) - 1))
#  elif TIMER2__PERIOD <= 256*256
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_256 | TIMER2_CONF_TOP((TIMER2__PERIOD/256) - 1))
#  elif TIMER2__PERIOD <= 256*1024
#    define TIMER2__CONF__STARTED  (TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_1024 | TIMER2_CONF_TOP((TIMER2__PERIOD/1024) - 1))
#  else
#    error "Period setting for Timer 2 is out of range"
#  endif
#endif


INLINE void timer2__init(void) {
#ifdef TIMER2__COMPARE_A__INTERRUPT__ENABLED
    timer2__compare_a__interrupt__enabled__set(1);
#endif

#ifdef TIMER2__COMPARE_B__INTERRUPT__ENABLED
    timer2__compare_b__interrupt__enabled__set(1);
#endif

#if defined(TIMER2__CONF__INITIALIZED)
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2__CONF__INITIALIZED);
#endif
}


#if defined(TIMER2__CONF__INITIALIZED) && defined(TIMER2__CONF__STARTED)
INLINE void timer2__start(void) {
    timer2__value__set(0);
    timer2__switch_conf(TIMER2__CONF__INITIALIZED, TIMER2__CONF__STARTED);
}

INLINE void timer2__stop(void) {
    timer2__switch_conf(TIMER2__CONF__STARTED, TIMER2__CONF__INITIALIZED);
}
#endif

#endif


#endif
