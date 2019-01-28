#ifndef __DRIVERS__OUT__LCD_BACKLIGHT_PWM_H
#define __DRIVERS__OUT__LCD_BACKLIGHT_PWM_H

#include <stdint.h>
#include <avr/io.h>

#if defined(__AVR_ATmega16__)

// LCD backlight control circuit is attached to OC2 (PD7)
// To control brightness, PWM signal is generated on OC2.

inline uint8_t lcd_backlight_pwm__get(void) {
    return OCR2;
}

inline void lcd_backlight_pwm__set(const uint8_t v) {
    OCR2=v;
}

// start timer 2, fast pwm, no-inverting out at OC2, clk/256
inline void lcd_backlight_pwm__start(void) {
    TCCR2 = _BV(WGM20)|_BV(WGM21)|_BV(COM21)|_BV(CS22)|_BV(CS21);
}

inline void lcd_backlight_pwm__stop(void) {
    TCCR2 = 0;
}


#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    #error "Unsupported MCU"
#else
    #error "Unsupported MCU"
#endif

#endif

