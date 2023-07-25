#ifndef __DRIVERS_IN_WATER_LEAK_SENSORS_H
#define __DRIVERS_IN_WATER_LEAK_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void water_leak_sensor__a__init(void) {
    ENABLE_PULLUP(WATER_LEAK_SENSOR__A);
}

inline bool water_leak_sensor__a__get(void) {
    return IS_1(WATER_LEAK_SENSOR__A);
}


static inline void water_leak_sensor__b__init(void) {
    ENABLE_PULLUP(WATER_LEAK_SENSOR__B);
}

inline bool water_leak_sensor__b__get(void) {
    return IS_1(WATER_LEAK_SENSOR__B);
}


#ifdef __AVR_ATmega16__

static inline void water_leak_sensor__c__init(void) {
    ENABLE_PULLUP(WATER_LEAK_SENSOR__C);
}

inline bool water_leak_sensor__c__get(void) {
    return IS_1(WATER_LEAK_SENSOR__C);
}


static inline void water_leak_sensor__d__init(void) {
    ENABLE_PULLUP(WATER_LEAK_SENSOR__D);
}

inline bool water_leak_sensor__d__get(void) {
    return IS_1(WATER_LEAK_SENSOR__D);
}

#else

static inline void water_leak_sensor__c__init(void) {
}

inline bool water_leak_sensor__c__get(void) {
    return true;
}


static inline void water_leak_sensor__d__init(void) {
}

inline bool water_leak_sensor__d__get(void) {
    return true;
}

#endif

#endif
