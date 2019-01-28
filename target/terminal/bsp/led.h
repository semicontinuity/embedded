#ifndef __LED_H
#define __LED_H

#include "cpu/avr/gpio.h"


inline void led__init(void)       { USE_AS_OUTPUT(LED); }
inline void led__on(void)         { OUT_1(LED); }
inline void led__off(void)        { OUT_0(LED); }


#endif