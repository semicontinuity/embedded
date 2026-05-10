// =============================================================================
// Siren #2 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__SIREN2_H
#define __DRIVERS__OUT__SIREN2_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


extern uint8_t siren2__state;


inline uint8_t siren2__get(void) {
    return siren2__state;
}

inline void siren2__set(const uint8_t value) {
    siren2__state = value;
    if (value)
        OUT_1(OUT__SIREN2);
    else
        OUT_0(OUT__SIREN2);
}

inline void siren2__on(void) {
    siren2__set(1);
}

inline void siren2__off(void) {
    siren2__set(0);
}

inline bool siren2__is_on(void) {
    return siren2__state;
}

/**
 * Initialize the siren #2 driver.
 * The valve control pin is forcibly driven low,
 * to ensure that siren is off (for the case of reset or brown-out).
 */
inline void siren2__init(void) {
    USE_AS_OUTPUT(OUT__SIREN2);
    siren2__off();
}

#endif