// =============================================================================
// Timer 0 driver
// Counts always from 0 to 255
// =============================================================================

#ifndef __CPU_AVR_TIMER0_H
#define __CPU_AVR_TIMER0_H

#include <stdint.h>
#include <avr/io.h>

// Generic "Compare" callback for devices with at least 1 OC unit.
#ifdef timer0__comp__run
INLINE void timer0__comp__run(void);
#endif

// Generic "Overflow" callback.
#ifdef timer0__overflow__run
INLINE void timer0__overflow__run(void);
#endif


#define TIMER0_MODE_STOPPED             (0)
#define TIMER0_MODE_RUN_NO_PRESCALER	(                        _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_8     (            _BV(CS01)            )
#define TIMER0_MODE_RUN_PRESCALER_64    (            _BV(CS01) | _BV(CS00))
#define TIMER0_MODE_RUN_PRESCALER_256   (_BV(CS02)                        )
#define TIMER0_MODE_RUN_PRESCALER_1024  (_BV(CS02)             | _BV(CS00))
#define TIMER0_MODE_RUN_EXT_CLK_FALLING (_BV(CS02) | _BV(CS01)            )
#define TIMER0_MODE_RUN_EXT_CLK_RISING  (_BV(CS02) | _BV(CS01) | _BV(CS00))


#if defined(TIMER0__COMPARE_UNITS)
#  error "Must not define TIMER0__COMPARE_UNITS"
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
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)\
 || defined(__AVR_AT90USB82__)\
 || defined(__AVR_AT90USB162__)\
 || defined(__AVR_ATtiny25__)\
 || defined(__AVR_ATtiny45__)\
 || defined(__AVR_ATtiny85__)


#  define timer0__value__REGISTER                       (TCNT0)
#  define TIMER0__COMPARE_UNITS	                        (2)

#  define timer0__overflow__interrupt__enabled__BIT     (TOIE0)
#  define timer0__overflow__interrupt__pending__BIT     (TOV0)

#  define timer0__compare_a__value                      (OCR0A)
#  define timer0__compare_a__interrupt__enabled__BIT    (OCIE0A)

#  define timer0__compare_a__interrupt__pending__BIT    (OCF0A)
#  define timer0__compare_a__interrupt__VECTOR          TIMER0_COMPA_vect

#  define timer0__compare_b__value                      (OCR0B)
#  define timer0__compare_b__interrupt__enabled__BIT    (OCIE0B)

#  define timer0__compare_b__interrupt__pending__BIT    (OCF0B)
#  define timer0__compare_b__interrupt__VECTOR          TIMER0_COMPB_vect


#if defined(__AVR_ATtiny25__)\
 || defined(__AVR_ATtiny45__)\
 || defined(__AVR_ATtiny85__)
#  define timer0__overflow__interrupt__enabled__HOST    (TIMSK)
#  define TIMER0__OVERFLOW__INTERRUPT__PENDING__HOST    (TIFR)
#  define timer0__compare_a__interrupt__enabled__HOST   (TIMSK)
#  define timer0__compare_a__interrupt__pending__HOST   (TIFR)
#  define timer0__compare_b__interrupt__enabled__HOST   (TIMSK)
#  define timer0__compare_b__interrupt__pending__HOST   (TIFR)
#else
#  define timer0__overflow__interrupt__enabled__HOST    (TIMSK0)
#  define timer0__overflow__interrupt__pending__HOST    (TIFR0)
#  define timer0__compare_a__interrupt__enabled__HOST   (TIMSK0)
#  define timer0__compare_a__interrupt__pending__HOST   (TIFR0)
#  define timer0__compare_b__interrupt__enabled__HOST   (TIMSK0)
#  define timer0__compare_b__interrupt__pending__HOST   (TIFR0)
#endif


#elif defined(__AVR_ATmega8__)\
 || defined(__AVR_AT90S2313__)


#  define timer0__value__REGISTER                       (TCNT0)
#  define TIMER0__COMPARE_UNITS	                        (0)
#  define timer0__overflow__interrupt__enabled__HOST    (TIMSK)
#  define timer0__overflow__interrupt__enabled__BIT     (TOIE0)
#  define timer0__overflow__interrupt__pending__HOST    (TIFR)
#  define timer0__overflow__interrupt__pending__BIT     (TOV0)



#elif defined(__AVR_ATmega16__)\
 || defined(__AVR_ATmega32__)\
 || defined(__AVR_ATmega8535__)


#  define timer0__value__REGISTER                       (TCNT0)

#  define TIMER0__COMPARE_UNITS	                        (1)
#  define timer0__overflow__interrupt__enabled__HOST    (TIMSK)
#  define timer0__overflow__interrupt__enabled__BIT     (TOIE0)
#  define timer0__overflow__interrupt__pending__HOST    (TIFR)
#  define timer0__overflow__interrupt__pending__BIT     (TOV0)

#  define timer0__compare_a__value                      (OCR0)
#  define timer0__compare_a__interrupt__enabled__HOST   (TIMSK)
#  define timer0__compare_a__interrupt__enabled__BIT    (OCIE0)
#  define timer0__compare_a__interrupt__pending__HOST   (TIFR)
#  define timer0__compare_a__interrupt__pending__BIT    (OCF0)
#  define timer0__compare_a__interrupt__VECTOR          TIMER0_COMP_vect


#else

#   error "Unsupported MCU"

#endif


#if defined(__AVR_AT90S2313__)
#define timer0__overflow__interrupt__VECTOR TIMER0_OVF0_vect
#else
#define timer0__overflow__interrupt__VECTOR TIMER0_OVF_vect
#endif


static inline void timer0__value__set(const uint8_t value) {
    timer0__value__REGISTER = value;
}

static inline uint8_t timer0__value__get(void) {
    return timer0__value__REGISTER;
}

inline static uint8_t timer0__overflow__interrupt__pending__get(void) {
    return timer0__overflow__interrupt__pending__HOST & _BV(timer0__overflow__interrupt__pending__BIT);
}

inline static void timer0__overflow__interrupt__pending__clear(void) {
    timer0__overflow__interrupt__pending__HOST |= _BV(timer0__overflow__interrupt__pending__BIT);
}

inline static void timer0__overflow__interrupt__enable(void) {
    timer0__overflow__interrupt__enabled__HOST |= _BV(timer0__overflow__interrupt__enabled__BIT);
}

inline static void timer0__overflow__interrupt__disable(void) {
    timer0__overflow__interrupt__enabled__HOST &= ~_BV(timer0__overflow__interrupt__enabled__BIT);
}

inline static void timer0__overflow__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) timer0__overflow__interrupt__enable(); else timer0__overflow__interrupt__disable();
}

inline static uint8_t timer0__overflow__interrupt__enabled__get(void) {
    return timer0__overflow__interrupt__enabled__HOST & _BV(timer0__overflow__interrupt__enabled__BIT);
}


#if TIMER0__COMPARE_UNITS >= 1

inline static void timer0__compare_a__value__set(const uint8_t value) {
    timer0__compare_a__value = value;
}

inline static uint8_t timer0__compare_a__value__get(void) {
    return timer0__compare_a__value;
}

inline static uint8_t timer0__compare_a__interrupt__is_enabled(void) {
    return timer0__compare_a__interrupt__enabled__HOST & _BV(timer0__compare_a__interrupt__enabled__BIT);
}

inline static void timer0__compare_a__interrupt__enable(void) {
    timer0__compare_a__interrupt__enabled__HOST |= _BV(timer0__compare_a__interrupt__enabled__BIT);
}

inline static void timer0__compare_a__interrupt__disable(void) {
    timer0__compare_a__interrupt__enabled__HOST &= ~_BV(timer0__compare_a__interrupt__enabled__BIT);
}

inline static void timer0__compare_a__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) timer0__compare_a__interrupt__enable(); else timer0__compare_a__interrupt__disable();
}

inline static void timer0__ctc__interrupt__enable(void) {
    timer0__compare_a__interrupt__enable();
}

inline static void timer0__ctc__interrupt__disable(void) {
    timer0__compare_a__interrupt__disable();
}

inline static uint8_t timer0__compare_a__interrupt__pending__get(void) {
    return timer0__compare_a__interrupt__pending__HOST & _BV(timer0__compare_a__interrupt__pending__BIT);
}

inline static void timer0__compare_a__interrupt__pending__clear(void) {
    timer0__compare_a__interrupt__pending__HOST |= _BV(timer0__compare_a__interrupt__pending__BIT);
}

#endif


#if TIMER0__COMPARE_UNITS >= 2

inline static void timer0__compare_b__value__set(const uint8_t value) {
    timer0__compare_b__value = value;
}

inline static uint8_t timer0__compare_b__value__get(void) {
    return timer0__compare_b__value;
}

inline static void timer0__compare_b__interrupt__enable(void) {
    timer0__compare_b__interrupt__enabled__HOST |= _BV(timer0__compare_b__interrupt__enabled__BIT);
}

inline static void timer0__compare_b__interrupt__disable(void) {
    timer0__compare_b__interrupt__enabled__HOST &= ~_BV(timer0__compare_b__interrupt__enabled__BIT);
}

inline static void timer0__compare_b__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) timer0__compare_b__interrupt__enable(); else timer0__compare_b__interrupt__disable();
}

inline static uint8_t timer0__compare_b__interrupt__pending__get(void) {
    return timer0__compare_b__interrupt__pending__HOST & _BV(timer0__compare_b__interrupt__pending__BIT);
}

inline static void timer0__compare_b__interrupt__pending__clear(void) {
    timer0__compare_b__interrupt__pending__HOST |= _BV(timer0__compare_b__interrupt__pending__BIT);
}

#endif


#if TIMER0__COMPARE_UNITS==0
#  include "cpu/avr/timer0__0oc.h"
#elif TIMER0__COMPARE_UNITS==1
#  include "cpu/avr/timer0__1oc.h"
#elif TIMER0__COMPARE_UNITS==2
#  include "cpu/avr/timer0__2oc.h"
#endif


#endif
