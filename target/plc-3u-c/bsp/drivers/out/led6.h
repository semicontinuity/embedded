// =============================================================================
// LED6 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED6_H
#define __DRIVERS__OUT__LED6_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set LED6 line value.
 */
inline void led6__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED6);
    else
        OUT_0(OUT__LED6);
}


/**
 * Initialize the LED6 line driver.
 */
inline void led6__init(void) {
    USE_AS_OUTPUT(OUT__LED6);
}

#endif