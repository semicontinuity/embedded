// =============================================================================
// PCINT2 driver
// =============================================================================

#ifndef __CPU_AVR_PIN_CHANGE_INT2_H
#define __CPU_AVR_PIN_CHANGE_INT2_H

#include <avr/io.h>
#include <stdint.h>


#if defined(__AVR_ATmega48__) ||\
    defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega328P__)

#define PIN_CHANGE_INT2__ENABLED__HOST     (PCICR)
#define PIN_CHANGE_INT2__PENDING__HOST     (PCIFR)
#define PIN_CHANGE_INT2__MASK              (PCMSK2)

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)

#   error "Unsupported MCU"

#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)

#   error "Unsupported MCU"

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#   error "Unsupported MCU"

#else

#   error "Unsupported MCU"

#endif



INLINE void pin_change_int2__mask__set(const uint8_t mask) {
    PIN_CHANGE_INT2__MASK = mask;
}


INLINE void pin_change_int2__start(void) {
    PIN_CHANGE_INT2__ENABLED__HOST |= (1<<PCIE2);
}


INLINE void pin_change_int2__stop(void) {
    PIN_CHANGE_INT2__ENABLED__HOST &= ~(1<<PCIE2);
}


#ifndef pin_change_int2__run__attrs
#define pin_change_int2__run__attrs
#endif

INLINE void pin_change_int2__run(void) pin_change_int2__run__attrs;

#endif
