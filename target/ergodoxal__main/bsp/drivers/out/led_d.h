// =============================================================================
// LED D driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_D_H
#define __DRIVERS__OUT__LED_D_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


/**
 * Toggle LED D.
 */
inline void led_d__toggle(void) {
    TOGGLE(OUT__LED_D);
}


/**
 * Set LED D value.
 */
inline void led_d__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_D);
    else
        OUT_0(OUT__LED_D);
}


/**
 * Copy LED D bit value from the specified bit of the supplied argument.
 */
inline void led_d__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_D), SIGNAL_PIN(OUT__LED_D), value, bit);
}


/**
 * Initialize LED D line driver.
 */
inline void led_d__init(void) {
    __asm__ __volatile__("led_d__init:");
    USE_AS_OUTPUT(OUT__LED_D);
}

#endif