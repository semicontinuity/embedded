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
        OUT_1(RTS);
    else
        OUT_0(RTS);
}


/**
 * Initialize the RTS line driver.
 * The out pin is forcibly driven low,
 * to ensure that RTS is off upon initialization.
 */
inline void rts__init(void) {
    USE_AS_OUTPUT(RTS);
    rts__set(0);
}

#endif