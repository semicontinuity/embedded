// =============================================================================
// LCD backlight fader.
// Controls the LCD backlight PWM driver: starts, stops, and adjusts duty cycle.
// 
// When brightness=0, actually, a small pulse is generated
// Ideally, duty cycle should be changed on Timer Compare interrupt.
// Currently, brightness changes non-uniformly around 0, but it is not noticeable.
// =============================================================================

#include "drivers/out/lcd_backlight_pwm.h"
#include "services/lcd_backlight_fader.h"

uint8_t  lcd_backlight_fader__settings__brightness_target;
 int8_t  lcd_backlight_fader__settings__brightness_change_step;


/**
 * Request fading with the specified parameters.
 * The change is effective on the next run of run() function.
 */
void lcd_backlight_fader__settings__set(const uint8_t brightness_target, const int8_t brightness_change_step) {
    const uint8_t brightness = lcd_backlight_pwm__get();
    if (brightness != brightness_target) {
        lcd_backlight_fader__settings__brightness_target      = brightness_target;
        lcd_backlight_fader__settings__brightness_change_step = brightness_change_step;

        if (brightness == 0) {
            lcd_backlight_pwm__start();
        }
    }    
} 


/**
 * Called periodically.
 */
void lcd_backlight_fader__run(void) {
    if (lcd_backlight_fader__settings__brightness_change_step != 0) {
        const uint8_t new_brightness = lcd_backlight_pwm__get() + lcd_backlight_fader__settings__brightness_change_step;
        lcd_backlight_pwm__set(new_brightness);
        if (new_brightness == lcd_backlight_fader__settings__brightness_target) {
            lcd_backlight_fader__settings__brightness_change_step = 0;
            if (new_brightness == 0) lcd_backlight_pwm__stop(); 
        }
    }
}
