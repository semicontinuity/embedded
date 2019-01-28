#ifndef __LCD_BACKLIGHT_SERVICE_H
#define __LCD_BACKLIGHT_SERVICE_H

#include <stdint.h>
#include <avr/sfr_defs.h>
#include "cpu/avr/gpio.h"

#if defined(__AVR_ATmega16__)

// LCD backlight control circuit is attached to OC2 (PD7)
// To control brightness, PWM signal is generated on OC2.

inline uint8_t lcd_backlight_service__pwm__get(void) {
    return OCR2;
}

inline void lcd_backlight_service__pwm__set(uint8_t v) {
    OCR2=v;
}

inline void lcd_backlight_service__init(void) {
    USE_AS_OUTPUT(MT12864_BACKLIGHT);
}

// start timer 2, fast pwm, no-inverting out at OC2, clk/256
inline void lcd_backlight_service__pwm__start(void) {
    TCCR2 = _BV(WGM20)|_BV(WGM21)|_BV(COM21)|_BV(CS22)|_BV(CS21);
}

inline void lcd_backlight_service__pwm__stop(void) {
    TCCR2 = 0;
}

void lcd_backlight_service__signal(void);

void lcd_backlight_service__run(void);



#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    #error "Unsupported MCU"
#else
    #error "Unsupported MCU"
#endif

#endif

