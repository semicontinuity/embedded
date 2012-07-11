#ifndef __LCD_BACKLIGHT_FADING_H
#define __LCD_BACKLIGHT_FADING_H

// start timer 2, fast pwm, no-inverting out at OC2, clk/256
#define lcd_backlight_start() { TCCR2 = _BV(WGM20)|_BV(WGM21)|_BV(COM21)|_BV(CS22)|_BV(CS21); }

#define lcd_backlight_stop() { TCCR2 = 0; }

#endif

