#ifndef __DRIVERS_IN_VALVE_LIMIT_SWITCHES_H
#define __DRIVERS_IN_VALVE_LIMIT_SWITCHES_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void valve_limit_switch__a__init(void) {
    ENABLE_PULLUP(VALVE_LIMIT_SWITCH__A);
}

inline bool valve_limit_switch__a__is_on(void) {
    return IS_1(VALVE_LIMIT_SWITCH__A);
}


static inline void valve_limit_switch__b__init(void) {
    ENABLE_PULLUP(VALVE_LIMIT_SWITCH__B);
}

inline bool valve_limit_switch__b__is_on(void) {
    return IS_1(VALVE_LIMIT_SWITCH__B);
}


static inline void valve_limit_switch__c__init(void) {
    ENABLE_PULLUP(VALVE_LIMIT_SWITCH__C);
}

inline bool valve_limit_switch__c__is_on(void) {
    return IS_1(VALVE_LIMIT_SWITCH__C);
}


static inline void valve_limit_switch__d__init(void) {
    ENABLE_PULLUP(VALVE_LIMIT_SWITCH__D);
}

inline bool valve_limit_switch__d__is_on(void) {
    return IS_1(VALVE_LIMIT_SWITCH__D);
}


#endif
