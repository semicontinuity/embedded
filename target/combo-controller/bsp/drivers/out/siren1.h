// =============================================================================
// Siren #1 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__SIREN1_H
#define __DRIVERS__OUT__SIREN1_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


extern uint8_t siren1__state;


inline uint8_t siren1__get(void) {
    return siren1__state;
}

inline void siren1__set(const uint8_t value) {
    siren1__state = value;
    if (value)
        OUT_1(OUT__SIREN1);
    else
        OUT_0(OUT__SIREN1);
}

inline void siren1__on(void) {
    siren1__set(1);
}

inline void siren1__off(void) {
    siren1__set(0);
}

inline bool siren1__is_on(void) {
    return siren1__state;
}

/**
 * Initialize the siren #1 driver.
 * The valve control pin is forcibly driven low,
 * to ensure that siren is off (for the case of reset or brown-out).
 */
inline void siren1__init(void) {
    USE_AS_OUTPUT(OUT__SIREN1);
    siren1__off();
}

#endif