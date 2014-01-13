// =============================================================================
// INT1 driver
// =============================================================================

#ifndef __CPU_AVR_INT1_H
#define __CPU_AVR_INT1_H

#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 


inline static void int1__init(void) {
#ifdef INT1__PULLUP
    PORTD |= (1<<3); // INT1 is on PD3 pin
#endif
    // external interrupt from INT1 pin, falling edge
    // interrupt on INT1 pin falling edge
    EICRA = (EICRA | (1<<ISC11)) & ~(1<<ISC10);
}


inline static void int1__start(void) {
    // Enable interrupt from INT1
    EIMSK |= (1<<INT1);
}


#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)


inline static void int1__init(void) {
#ifdef INT1__PULLUP
    PORTD |= (1<<3); // INT1 is on PD3 pin
#endif
    MCUCR = (MCUCR | (1<<ISC11)) & ~(1<<ISC10);
}


inline static void int1__start(void) {
    // Enable interrupt from INT1
    GICR  |= (1<<INT1);	// enable external interrupt from INT1 pin
}


#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)


inline static void int1__init(void) {
#ifdef INT1__PULLUP
    PORTD |= (1<<3); // INT1 is on PD3 pin
#endif
    // interrupt from INT1 pin, falling edge
    MCUCR = (MCUCR | (1<<ISC11)) & ~(1<<ISC10);
}


inline static void int1__start(void) {
    // Enable interrupt from INT1
    GIMSK |= (1<<INT1);	// enable external interrupt from INT1 pin
}


#else

#   error "Unsupported MCU"

#endif


#ifndef int1__run__attrs
#define int1__run__attrs
#endif

INLINE void int1__run(void) int1__run__attrs;

#endif