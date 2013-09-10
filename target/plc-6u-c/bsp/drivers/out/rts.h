// =============================================================================
// RTS line driver.
// =============================================================================

#ifndef __DRIVERS__OUT__RTS_H
#define __DRIVERS__OUT__RTS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void rts__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__RTS);
    else
        OUT_0(OUT__RTS);
}


/**
 * Initialize the RTS line driver.
 * The out pin is forcibly driven low,
 * to ensure that amplifier relay is off (for the case of reset or brown-out).
 */
inline void rts__init(void) {
    USE_AS_OUTPUT(OUT__RTS);
    rts__set(0);
}

#endif