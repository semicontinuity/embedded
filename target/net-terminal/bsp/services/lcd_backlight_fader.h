#ifndef __SERVICES__LCD_BACKLIGHT_FADER_H
#define __SERVICES__LCD_BACKLIGHT_FADER_H

#include <stdint.h>

void lcd_backlight_fader__settings__set(const uint8_t brightness_target, const int8_t brightness_change_step);

INLINE void lcd_backlight_fader__run(void);

#endif

