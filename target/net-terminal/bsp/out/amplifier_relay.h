// =============================================================================
// Amplifier relay driver.
// =============================================================================

#ifndef __OUT__AMPLIFIER_RELAY_H
#define __OUT__AMPLIFIER_RELAY_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void out__amplifier_relay__on(void) {
    OUT_1(OUT__AMPLIFIER_RELAY);
}

inline void out__amplifier_relay__off(void) {
    OUT_0(OUT__AMPLIFIER_RELAY);
}

inline bool out__amplifier_relay__is_on(void) {
    return IS_1(OUT__AMPLIFIER_RELAY);
}



/**
 * Initialize the amplifier relay driver.
 * The out pin is forcibly driven low,
 * to ensure that amplifier relay is off (for the case of reset or brown-out).
 */
inline void out__amplifier_relay__init(void) {
    USE_AS_OUTPUT(OUT__AMPLIFIER_RELAY);
    out__amplifier_relay__off();
}

#endif