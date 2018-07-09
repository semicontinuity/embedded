// =============================================================================
// Debug LED (at pin D4) driver.
// =============================================================================

#ifndef __DRIVERS__OUT__DEBUG_LED_D4_H
#define __DRIVERS__OUT__DEBUG_LED_D4_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle Debug LED D4.
 */
inline void debug_led_d4__toggle(void) {
    TOGGLE(OUT__DEBUG_LED_D4);
}


/**
 * Set Debug LED D4 value.
 */
inline void debug_led_d4__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__DEBUG_LED_D4);
    else
        OUT_0(OUT__DEBUG_LED_D4);
}


/**
 * Initialize Debug LED D4 line driver.
 */
inline void debug_led_d4__init(void) {
    USE_AS_OUTPUT(OUT__DEBUG_LED_D4);
}

#endif