#ifndef __OUT_BUZZER_H
#define __OUT_BUZZER_H

#include "cpu/avr/gpio.h"


static inline void buzzer__init(void) {
    USE_AS_OUTPUT(BUZZER);
}


static inline void buzzer__on(void) {
    OUT_1(BUZZER);
}


static inline void buzzer__off(void) {
    OUT_0(BUZZER);
}


#endif