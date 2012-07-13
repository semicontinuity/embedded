#include "device.h"
#include <avr/pgmspace.h>

#include "lcd_backlight_service.h"

uint16_t fadeOutTimeout = 0;
uint8_t dutyFactorDelta = 0;
uint8_t targetDutyFactor;




// Backlighting is done with PWM on OC2 output (driven by Timer 2)

void lcd_backlight_service__signal(void)
{
    lcd_backlight_service__pwm__start();
    fadeOutTimeout = LCD_BACKLIGHT_FADEOUT_TIMEOUT;
    if (lcd_backlight_service__pwm__get() == 0)	// no backlight, no keyboard events for long time
    {
        dutyFactorDelta = LCD_BACKLIGHT_INC_BRIGHTNESS_STEP;
        targetDutyFactor = LCD_BACKLIGHT_MAX_BRIGHTNESS; // start increasing duty factor until this value
    }
} 


// Called periodically
void lcd_backlight_service__run(void)
{
    if (fadeOutTimeout != 0)
    {
        --fadeOutTimeout;
        if (fadeOutTimeout == 0) // just reached 0 - timeout
        {
            dutyFactorDelta = LCD_BACKLIGHT_DEC_BRIGHTNESS_STEP; // start slowly decreasing duty factor
            targetDutyFactor = LCD_BACKLIGHT_MIN_BRIGHTNESS; // start decreasing duty factor until this value
        }
    }

    if (dutyFactorDelta != 0)
    {
        lcd_backlight_service__pwm__set(lcd_backlight_service__pwm__get() + dutyFactorDelta);
        if (lcd_backlight_service__pwm__get() == targetDutyFactor)
        {
            dutyFactorDelta = 0;
            // when brightness=0, actually, a small pulse is generated
            // ideally, pwm should be switched off at next cycle
            // currently, brightness changes non-uniformly around 0, but it is not noticeable.
            if (lcd_backlight_service__pwm__get() == 0) lcd_backlight_service__pwm__stop(); 
        }
    }
}