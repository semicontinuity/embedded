// =============================================================================
// Red LED driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_RED_H
#define __DRIVERS__OUT__LED_RED_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void led_red__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_RED);
    else
        OUT_0(OUT__LED_RED);
}


/**
 * Initialize the LED driver.
 */
inline void led_red__init(void) {
    USE_AS_OUTPUT(OUT__LED_RED);
    led_red__set(0);
}

#endif