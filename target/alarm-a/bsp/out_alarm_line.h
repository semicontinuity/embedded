#ifndef __OUT_ALARM_LINE_H
#define __OUT_ALARM_LINE_H

#include "cpu/avr/gpio.h"


static inline void alarm_line__init(void) {
    USE_AS_OUTPUT(ALARM_LINE);
}


static inline void alarm_line__on(void) {
    OUT_1(ALARM_LINE);
}


static inline void alarm_line__off(void) {
    OUT_0(ALARM_LINE);
}


#endif