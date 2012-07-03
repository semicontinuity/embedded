#ifndef __LED_H
#define __LED_H

#include "device.h"
#include "cpu/avr/gpio.h"


inline void led_green__init(void)       { CONFIGURE_AS_OUTPUT(LED_GREEN); }
inline void led_green__on(void)	        { DRIVE_HIGH(LED_GREEN); }
inline void led_green__off(void)        { DRIVE_LOW(LED_GREEN); }


inline void led_red__init(void)         { CONFIGURE_AS_OUTPUT(LED_RED); }
inline void led_red__on(void)           { DRIVE_HIGH(LED_RED); }
inline void led_red__off(void)          { DRIVE_LOW(LED_RED); }


#endif