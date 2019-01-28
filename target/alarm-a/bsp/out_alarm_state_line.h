#ifndef __OUT_ALARM_STATE_LINE_H
#define __OUT_ALARM_STATE_LINE_H

#include "cpu/avr/gpio.h"


static inline void alarm_state_line__init(void) {
    USE_AS_OUTPUT(ALARM_STATE_LINE);
}


static inline void alarm_state_line__on(void) {
    OUT_1(ALARM_STATE_LINE);
}


static inline void alarm_state_line__off(void) {
    OUT_0(ALARM_STATE_LINE);
}


#endif