// =============================================================================
// Water valve driver.
// =============================================================================

#ifndef __DRIVERS__OUT__WATER_VALVE_H
#define __DRIVERS__OUT__WATER_VALVE_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void water_valve__on(void) {
    OUT_1(OUT__WATER_VALVE);
}

inline void water_valve__off(void) {
    OUT_0(OUT__WATER_VALVE);
}

inline bool water_valve__is_on(void) {
    return IS_1(OUT__WATER_VALVE);
}



/**
 * Initialize the water valve driver.
 * The valve control pin is forcibly driven low,
 * to ensure that valve is open (for the case of reset or brown-out).
 */
inline void water_valve__init(void) {
    USE_AS_OUTPUT(OUT__WATER_VALVE);
    water_valve__off();
}

#endif