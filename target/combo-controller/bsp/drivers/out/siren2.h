// =============================================================================
// Siren #2 driver.
// =============================================================================

#ifndef __OUT__SIREN2_H
#define __OUT__SIREN2_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void out__siren2__on(void) {
    OUT_1(OUT__SIREN2);
}

inline void out__siren2__off(void) {
    OUT_0(OUT__SIREN2);
}


inline bool out__siren2__is_on(void) {
    return IS_1(OUT__SIREN2);
}


/**
 * Initialize the siren #2 driver.
 * The valve control pin is forcibly driven low,
 * to ensure that siren is off (for the case of reset or brown-out).
 */
inline void out__siren2__init(void) {
    USE_AS_OUTPUT(OUT__SIREN2);
    out__siren2__off();
}

#endif