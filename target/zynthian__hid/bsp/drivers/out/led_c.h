// =============================================================================
// LED C driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_C_H
#define __DRIVERS__OUT__LED_C_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LED C.
 */
inline void led_c__toggle(void) {
    TOGGLE(OUT__LED_C);
}


/**
 * Set LED C value.
 */
inline void led_c__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_C);
    else
        OUT_0(OUT__LED_C);
}


/**
 * Initialize LED C line driver.
 */
inline void led_c__init(void) {
    USE_AS_OUTPUT(OUT__LED_C);
}

#endif