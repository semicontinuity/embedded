// =============================================================================
// Debug LED (at pin D7) driver.
// =============================================================================

#ifndef __DRIVERS__OUT__DEBUG_LED_LCD_D7_H
#define __DRIVERS__OUT__DEBUG_LED_LCD_D7_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle Debug LED D7.
 */
inline void debug_led_lcd_d7__toggle(void) {
    TOGGLE(OUT__DEBUG_LED_LCD_D7);
}


/**
 * Set Debug LED D7 value.
 */
inline void debug_led_lcd_d7__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__DEBUG_LED_LCD_D7);
    else
        OUT_0(OUT__DEBUG_LED_LCD_D7);
}


/**
 * Initialize Debug LED D7 line driver.
 */
inline void debug_led_lcd_d7__init(void) {
    USE_AS_OUTPUT(OUT__DEBUG_LED_LCD_D7);
}

#endif