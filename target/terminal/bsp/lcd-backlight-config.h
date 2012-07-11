#ifndef __LCD_BACKLIGHT_CONFIG_H
#define __LCD_BACKLIGHT_CONFIG_H

// LCD backlight control circuit is attached to OC2 (PD7)
// To control brightness, PWM signal is generated on OC2.

#define get_lcd_brightness() (OCR2)
#define set_lcd_brightness() (OCR2)
#define change_lcd_brightness(delta) (OCR2+=(delta))

// Max brightness must be divisible by inc. step
#define LCD_BACKLIGHT_FADEOUT_TIMEOUT (1000)
#define LCD_BACKLIGHT_INC_BRIGHTNESS_STEP (5)
#define LCD_BACKLIGHT_DEC_BRIGHTNESS_STEP (-1)
#define LCD_BACKLIGHT_MAX_BRIGHTNESS (60)
#define LCD_BACKLIGHT_MIN_BRIGHTNESS (0)

#endif
