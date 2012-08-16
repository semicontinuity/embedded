#ifndef __LED_H
#define __LED_H

#include "cpu/avr/gpio.h"


inline void led_green__init(void)       { USE_AS_OUTPUT(LED_GREEN); }
inline void led_green__on(void)	        { OUT_1(LED_GREEN); }
inline void led_green__off(void)        { OUT_0(LED_GREEN); }


inline void led_red__init(void)         { USE_AS_OUTPUT(LED_RED); }
inline void led_red__on(void)           { OUT_1(LED_RED); }
inline void led_red__off(void)          { OUT_0(LED_RED); }


#endif