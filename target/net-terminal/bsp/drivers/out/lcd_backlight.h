// =============================================================================
// LCD backlight control pin driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LCD_BACKLIGHT_H
#define __DRIVERS__OUT__LCD_BACKLIGHT_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"



inline void lcd_backlight__on(void) {
    OUT_1(LCD_BACKLIGHT);
}

inline void lcd_backlight__off(void) {
    OUT_0(LCD_BACKLIGHT);
}

inline bool lcd_backlight__is_on(void) {
    return IS_1(LCD_BACKLIGHT);
}

/**
 * Initialize the driver.
 * The pin function is Output Compare.
 */
inline void lcd_backlight__init(void) {
    USE_AS_OUTPUT(LCD_BACKLIGHT);
}

#endif