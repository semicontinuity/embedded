#include "device.h"
#include <avr/pgmspace.h>

#include "lcd-backlight-fading.h"

uint16_t fadeOutTimeout = 0;
uint8_t dutyFactorDelta = 0;
uint8_t targetDutyFactor;




// Backlighting is done with PWM on OC2 output (driven by Timer 2)

void lcd_backlight_request(void)
{
    lcd_backlight_start();
    fadeOutTimeout = LCD_BACKLIGHT_FADEOUT_TIMEOUT;
    if (get_lcd_brightness() == 0)	// no backlight, no keyboard events for long time
    {
        dutyFactorDelta = LCD_BACKLIGHT_INC_BRIGHTNESS_STEP;
        targetDutyFactor = LCD_BACKLIGHT_MAX_BRIGHTNESS; // start increasing duty factor until this value
    }
} 


void lcd_backlight_run(void)
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
        change_lcd_brightness(dutyFactorDelta);
        if (get_lcd_brightness() == targetDutyFactor)
        {
            dutyFactorDelta = 0;
            // when brightness=0, actually, a small pulse is generated
            // ideally, pwm should be switched off at next cycle
            // currently, brightness changes non-uniformly around 0, but it is not noticeable.
            if (get_lcd_brightness() == 0) lcd_backlight_stop(); 
        }
    }
}