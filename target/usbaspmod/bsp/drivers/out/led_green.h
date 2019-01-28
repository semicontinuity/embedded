// =============================================================================
// Green LED driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_GREEN_H
#define __DRIVERS__OUT__LED_GREEN_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void led_green__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_GREEN);
    else
        OUT_0(OUT__LED_GREEN);
}


/**
 * Initialize the LED driver.
 */
inline void led_green__init(void) {
    USE_AS_OUTPUT(OUT__LED_GREEN);
    led_green__set(0);
}

#endif