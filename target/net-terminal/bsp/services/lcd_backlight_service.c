// =============================================================================
// LCD backlight service.
// Controls LCD backlight fader.
//
// Fading into full brightness happens on call to lcd_backlight_service__signal.
// Fading out happens when there are no calls to lcd_backlight_service__signal
// for a specified time (LCD_BACKLIGHT_SERVICE__FADEOUT_TIMEOUT).
// =============================================================================

#include "services/lcd_backlight_fader.h"
#include "services/lcd_backlight_service.h"
#include <stdint.h>

uint16_t lcd_backlight_service__time_to_fade_out;


/**
 * Request fading into full brightness.
 * Resets the time to fade out.
 */
void lcd_backlight_service__signal(void) {
    lcd_backlight_service__time_to_fade_out = LCD_BACKLIGHT_SERVICE__FADEOUT_TIMEOUT;
    lcd_backlight_fader__settings__set(LCD_BACKLIGHT_SERVICE__MAX_BRIGHTNESS, LCD_BACKLIGHT_SERVICE__INC_BRIGHTNESS_STEP);
} 


/**
 * Called periodically.
 * If fadeOutTimeout has expired, start to fade out.
 */
void lcd_backlight_service__run(void) {
    if (lcd_backlight_service__time_to_fade_out != 0) {
        if (--lcd_backlight_service__time_to_fade_out == 0) { // just reached 0 - timeout
            lcd_backlight_fader__settings__set(LCD_BACKLIGHT_SERVICE__MIN_BRIGHTNESS, LCD_BACKLIGHT_SERVICE__DEC_BRIGHTNESS_STEP);
        }
    }
}