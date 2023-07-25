#ifndef __LED_ALARM_H
#define __LED_ALARM_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void led_alarm__init(void) {
    USE_AS_OUTPUT(LED_ALARM);
}


static inline void led_alarm__toggle(void) {
    TOGGLE(LED_ALARM);
}


static inline void led_alarm__on(void) {
    OUT_1(LED_ALARM);
}


static inline void led_alarm__off(void) {
    OUT_0(LED_ALARM);
}


/**
 * Set ALARM LED value.
 * 1 = ON, 0 = OFF
 */
inline void led_alarm__set(const uint8_t value) {
    if (value)
        OUT_1(LED_ALARM);
    else
        OUT_0(LED_ALARM);
}

inline bool led_alarm__is_set(void) {
    return IS_OUT_1(LED_ALARM);
}


#endif
