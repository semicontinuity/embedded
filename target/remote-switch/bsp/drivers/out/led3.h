// =============================================================================
// LED3 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED3_H
#define __DRIVERS__OUT__LED3_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LED1.
 */
inline void led3__toggle(void) {
    TOGGLE(OUT__LED3);
}


/**
 * Set LED3 line value.
 */
inline void led3__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED3);
    else
        OUT_0(OUT__LED3);
}


/**
 * Initialize the LED3 line driver.
 */
inline void led3__init(void) {
    USE_AS_OUTPUT(OUT__LED3);
}

#endif