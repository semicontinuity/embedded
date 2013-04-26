// =============================================================================
// Siren #2 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__SIREN2_H
#define __DRIVERS__OUT__SIREN2_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void siren2__on(void) {
    OUT_1(OUT__SIREN2);
}

inline void siren2__off(void) {
    OUT_0(OUT__SIREN2);
}


inline bool siren2__is_on(void) {
    return IS_1(OUT__SIREN2);
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