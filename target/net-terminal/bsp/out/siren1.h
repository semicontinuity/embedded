// =============================================================================
// Siren #1 driver.
// =============================================================================

#ifndef __OUT__SIREN1_H
#define __OUT__SIREN1_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void out__siren1__on(void) {
    OUT_1(OUT__SIREN1);
}

inline void out__siren1__off(void) {
    OUT_0(OUT__SIREN1);
}

inline bool out__siren1__is_on(void) {
    return IS_1(OUT__SIREN1);
}

/**
 * Initialize the siren #1 driver.
 * The valve control pin is forcibly driven low,
 * to ensure that siren is off (for the case of reset or brown-out).
 */
inline void out__siren1__init(void) {
    USE_AS_OUTPUT(OUT__SIREN1);
    out__siren1__off();
}

#endif