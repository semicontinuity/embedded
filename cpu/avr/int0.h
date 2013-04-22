// =============================================================================
// INT0 driver
// =============================================================================

#ifndef __CPU_AVR_INT0_H
#define __CPU_AVR_INT0_H

#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 


inline static void int0__init(void) {
#ifdef INT0__PULLUP
    PORTD |= (1<<2); // INT0 is on PD2 pin
#endif
    // interrupt from INT0 pin, falling edge
    EICRA = (1<<ISC01);
}


inline static void int0__start(void) {
    // Enable interrupt from INT0
    EIMSK |= (1<<INT0);
}


#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)


inline static void int0__init(void) {
#ifdef INT0__PULLUP
    PORTD |= (1<<2); // INT0 is on PD2 pin
#endif
    // interrupt from INT0 pin, falling edge
    MCUCR |= (1<<ISC01);
}


inline static void int0__start(void) {
    // Enable interrupt from INT0
    GICR  |= (1<<INT0);	// enable external interrupt from INT0 pin
}

#else

#   error "Unsupported MCU"

#endif


#ifndef int0__run__attrs
#define int0__run__attrs
#endif

INLINE void int0__run(void) int0__run__attrs;

#endif