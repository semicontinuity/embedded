#include "device.h"
#include <avr/pgmspace.h>

#include "lcd_backlight_service.h"

uint16_t lcd_backlight_service__fadeOutTimeout;
uint8_t  lcd_backlight_service__dutyFactorDelta;
uint8_t  lcd_backlight_service__targetDutyFactor;




// Backlighting is done with PWM on OC2 output (driven by Timer 2)

void lcd_backlight_service__signal(void)
{
    lcd_backlight_service__pwm__start();
    lcd_backlight_service__fadeOutTimeout = LCD_BACKLIGHT_SERVICE__FADEOUT_TIMEOUT;
    if (lcd_backlight_service__pwm__get() == 0)	// no backlight, no keyboard events for long time
    {
        lcd_backlight_service__dutyFactorDelta  = LCD_BACKLIGHT_SERVICE__INC_BRIGHTNESS_STEP;
        lcd_backlight_service__targetDutyFactor = LCD_BACKLIGHT_SERVICE__MAX_BRIGHTNESS; // start increasing duty factor until this value
    }
} 


// Called periodically
void lcd_backlight_service__run(void)
{
    if (lcd_backlight_service__fadeOutTimeout != 0)
    {
        --lcd_backlight_service__fadeOutTimeout;
        if (lcd_backlight_service__fadeOutTimeout == 0) // just reached 0 - timeout
        {
            lcd_backlight_service__dutyFactorDelta  = LCD_BACKLIGHT_SERVICE__DEC_BRIGHTNESS_STEP; // start slowly decreasing duty factor
            lcd_backlight_service__targetDutyFactor = LCD_BACKLIGHT_SERVICE__MIN_BRIGHTNESS; // start decreasing duty factor until this value
        }
    }

    if (lcd_backlight_service__dutyFactorDelta != 0)
    {
        lcd_backlight_service__pwm__set(lcd_backlight_service__pwm__get() + lcd_backlight_service__dutyFactorDelta);
        if (lcd_backlight_service__pwm__get() == lcd_backlight_service__targetDutyFactor)
        {
            lcd_backlight_service__dutyFactorDelta = 0;
            // when brightness=0, actually, a small pulse is generated
            // ideally, pwm should be switched off at next cycle
            // currently, brightness changes non-uniformly around 0, but it is not noticeable.
            if (lcd_backlight_service__pwm__get() == 0) lcd_backlight_service__pwm__stop(); 
        }
    }
}