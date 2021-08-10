// =============================================================================
// LED C driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_C_H
#define __DRIVERS__OUT__LED_C_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


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
 * Copy LED C bit value from the specified bit of the supplied argument.
 */
inline void led_c__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_C), SIGNAL_PIN(OUT__LED_C), value, bit);
}


/**
 * Initialize LED C line driver.
 */
inline void led_c__init(void) {
    __asm__ __volatile__("led_c__init:");
    USE_AS_OUTPUT(OUT__LED_C);
}

#endif