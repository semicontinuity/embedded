// =============================================================================
// RTS line driver.
// =============================================================================

#ifndef __DRIVERS__OUT__RTS_H
#define __DRIVERS__OUT__RTS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set RTS line value.
 * 1 = transmit, 0 = receive
 */
inline void rts__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__RTS);
    else
        OUT_0(OUT__RTS);
}


/**
 * Initialize the RTS line driver.
 * The out pin is forcibly driven low (receive).
 */
inline void rts__init(void) {
    USE_AS_OUTPUT(OUT__RTS);
    rts__set(0);
}

#endif