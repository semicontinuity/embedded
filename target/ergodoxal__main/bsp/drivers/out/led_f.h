// =============================================================================
// LED F driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_F_H
#define __DRIVERS__OUT__LED_F_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LED F.
 */
inline void led_f__toggle(void) {
    TOGGLE(OUT__LED_F);
}


/**
 * Set LED F value.
 */
inline void led_f__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_F);
    else
        OUT_0(OUT__LED_F);
}


/**
 * Initialize LED F line driver.
 */
inline void led_f__init(void) {
    __asm__ __volatile__("led_f__init:");
    USE_AS_OUTPUT(OUT__LED_F);
}

#endif