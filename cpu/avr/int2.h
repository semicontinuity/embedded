// =============================================================================
// INT2 driver
// =============================================================================

#ifndef __CPU_AVR_INT2_H
#define __CPU_AVR_INT2_H

#include <avr/io.h>


#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)

#define INT2__ENABLED__HOST     (GICR)
#define INT2__CONFIG__HOST      (MCUCSR)

#else

#   error "Unsupported MCU"

#endif



INLINE void int2__init(void) {
#ifdef INT2__PULLUP
    PORTB |= (1<<2); // INT2 is on PB2 pin
#endif
    // interrupt from INT2 pin, falling edge
    INT2__CONFIG__HOST &= ~(1<<ISC2);
}


INLINE void int2__start(void) {
    // Enable interrupt from INT2
    INT2__ENABLED__HOST |= (1<<INT2);
}


INLINE void int2__stop(void) {
    // Disable interrupt from INT2
    INT2__ENABLED__HOST &= ~(1<<INT2);
}


#ifndef int2__run__attrs
#define int2__run__attrs
#endif

INLINE void int2__run(void) int2__run__attrs;

#endif