#ifndef __BUZZER_H
#define __BUZZER_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void buzzer__init(void) {
    USE_AS_OUTPUT(BUZZER);
}


static inline void buzzer__toggle(void) {
    TOGGLE(BUZZER);
}


static inline void buzzer__on(void) {
    OUT_1(BUZZER);
}


static inline void buzzer__off(void) {
    OUT_0(BUZZER);
}


inline void buzzer__set(const uint8_t value) {
    if (value)
        OUT_1(BUZZER);
    else
        OUT_0(BUZZER);
}

inline bool buzzer__is_set(void) {
    return IS_OUT_1(BUZZER);
}


#endif
