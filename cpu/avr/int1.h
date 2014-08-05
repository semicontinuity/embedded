// =============================================================================
// INT1 driver
// =============================================================================

#ifndef __CPU_AVR_INT1_H
#define __CPU_AVR_INT1_H

#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 

#define INT1__ENABLED__HOST     (EIMSK)
#define INT1__CONFIG__HOST      (EICRA)

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)

#define INT1__ENABLED__HOST     (GICR)
#define INT1__CONFIG__HOST      (MCUCR)

#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)

#define INT1__ENABLED__HOST     (GIMSK)
#define INT1__CONFIG__HOST      (MCUCR)

#else

#   error "Unsupported MCU"

#endif



inline static void int1__init(void) {
#ifdef INT1__PULLUP
    PORTD |= (1<<3); // INT1 is on PD3 pin
#endif
    // interrupt from INT1 pin, falling edge
    INT1__CONFIG__HOST = (INT1__CONFIG__HOST | (1<<ISC11)) & ~(1<<ISC10);
}


inline static void int1__start(void) {
    // Enable interrupt from INT1
    INT1__ENABLED__HOST |= (1<<INT1);
}


inline static void int1__stop(void) {
    // Disable interrupt from INT1
    INT1__ENABLED__HOST &= ~(1<<INT1);
}


#ifndef int1__run__attrs
#define int1__run__attrs
#endif

INLINE void int1__run(void) int1__run__attrs;

#endif