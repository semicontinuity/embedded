// =============================================================================
// INT0 driver.
// (falling edge only)
// =============================================================================

#ifndef __CPU_AVR_INT0_H
#define __CPU_AVR_INT0_H

#include <avr/io.h>


#if defined(__AVR_ATmega48__) ||\
    defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega328P__)

#define INT0__PORT              (PORTD)
#define INT0__PIN               (2)
#define INT0__ENABLED__HOST     (EIMSK)
#define INT0__CONFIG__HOST      (EICRA)

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)

#define INT0__PORT              (PORTD)
#define INT0__PIN               (2)
#define INT0__ENABLED__HOST     (GICR)
#define INT0__CONFIG__HOST      (MCUCR)

#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)

#define INT0__PORT              (PORTD)
#define INT0__PIN               (2)
#define INT0__ENABLED__HOST     (GIMSK)
#define INT0__CONFIG__HOST      (MCUCR)

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#define INT0__PORT              (PORTB)
#define INT0__PIN               (2)
#define INT0__ENABLED__HOST     (GIMSK)
#define INT0__CONFIG__HOST      (MCUCR)

#else

#   error "Unsupported MCU"

#endif



INLINE void int0__init(void) {
#ifdef INT0__PULLUP
    INT0__PORT |= (1<<INT0__PIN);
#endif
    // interrupt from INT0 pin, falling edge
    INT0__CONFIG__HOST = (INT0__CONFIG__HOST | (1<<ISC01)) & ~(1<<ISC00);
}


INLINE void int0__start(void) {
    // Enable interrupt from INT0
    INT0__ENABLED__HOST |= (1<<INT0);
}


INLINE void int0__stop(void) {
    // Disable interrupt from INT0
    INT0__ENABLED__HOST &= ~(1<<INT0);
}


#ifndef int0__run__attrs
#define int0__run__attrs
#endif

INLINE void int0__run(void) int0__run__attrs;

#endif