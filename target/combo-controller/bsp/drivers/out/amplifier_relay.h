// =============================================================================
// Amplifier relay driver.
// =============================================================================

#ifndef __DRIVERS__OUT__AMPLIFIER_RELAY_H
#define __DRIVERS__OUT__AMPLIFIER_RELAY_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


extern uint8_t amplifier_relay__state;


inline void amplifier_relay__set(const uint8_t value) {
    amplifier_relay__state = value;
    if (value)
        OUT_1(OUT__AMPLIFIER_RELAY);
    else
        OUT_0(OUT__AMPLIFIER_RELAY);
}

inline void amplifier_relay__on(void) {
    amplifier_relay__set(1);
}

inline void amplifier_relay__off(void) {
    amplifier_relay__set(0);
}

inline bool amplifier_relay__is_on(void) {
    return IS_1(OUT__AMPLIFIER_RELAY);
}

inline uint8_t amplifier_relay__get(void) {
    return amplifier_relay__state;
}


/**
 * Initialize the amplifier relay driver.
 * The out pin is forcibly driven low,
 * to ensure that amplifier relay is off (for the case of reset or brown-out).
 */
inline void amplifier_relay__init(void) {
    USE_AS_OUTPUT(OUT__AMPLIFIER_RELAY);
    amplifier_relay__off();
}

#endif