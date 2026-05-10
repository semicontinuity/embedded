#ifndef __ALARM_STATE_H
#define __ALARM_STATE_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

inline void alarm_state__init(void)       { ENABLE_PULLUP(ALARM_STATE); }
inline uint8_t alarm_state__get(void)     { return IS_1(ALARM_STATE); }


#endif