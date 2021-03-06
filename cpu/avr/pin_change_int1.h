// =============================================================================
// PCINT1 driver
// =============================================================================

#ifndef __CPU_AVR_PIN_CHANGE_INT1_H
#define __CPU_AVR_PIN_CHANGE_INT1_H

#include <avr/io.h>
#include <stdint.h>


#if defined(__AVR_ATmega48__) ||\
    defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega328P__)

#define PIN_CHANGE_INT1__ENABLED__HOST     (PCICR)
#define PIN_CHANGE_INT1__PENDING__HOST     (PCIFR)
#define PIN_CHANGE_INT1__MASK              (PCMSK1)

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8535__)

#   error "Unsupported MCU"

#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)

#   error "Unsupported MCU"

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#   error "Unsupported MCU"

#else

#   error "Unsupported MCU"

#endif


INLINE uint8_t pin_change_int1__mask__get(void) {
    return PIN_CHANGE_INT1__MASK;
}

INLINE void pin_change_int1__mask__set(const uint8_t mask) {
    PIN_CHANGE_INT1__MASK = mask;
}


INLINE void pin_change_int1__start(void) {
    PIN_CHANGE_INT1__ENABLED__HOST |= (1 << PCIE1);
}

INLINE void pin_change_int1__stop(void) {
    PIN_CHANGE_INT1__ENABLED__HOST &= ~(1 << PCIE1);
}


#ifndef pin_change_int1__run__attrs
#define pin_change_int1__run__attrs
#endif

INLINE void pin_change_int1__run(void) pin_change_int1__run__attrs;

#endif
