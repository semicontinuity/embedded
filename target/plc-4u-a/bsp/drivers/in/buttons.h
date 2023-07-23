#ifndef __DRIVERS_IN_BUTTONS_H
#define __DRIVERS_IN_BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void button__a__init(void) {
    ENABLE_PULLUP(BUTTON__A);
}

inline bool button__a__is_on(void) {
    return IS_1(BUTTON__A);
}


static inline void button__b__init(void) {
    ENABLE_PULLUP(BUTTON__B);
}

inline bool button__b__is_on(void) {
    return IS_1(BUTTON__B);
}


static inline void button__c__init(void) {
    ENABLE_PULLUP(BUTTON__C);
}

inline bool button__c__is_on(void) {
    return IS_1(BUTTON__C);
}


static inline void button__d__init(void) {
    ENABLE_PULLUP(BUTTON__D);
}

inline bool button__d__is_on(void) {
    return IS_1(BUTTON__D);
}


static inline void button__e__init(void) {
    ENABLE_PULLUP(BUTTON__E);
}

inline bool button__e__is_on(void) {
    return IS_1(BUTTON__E);
}


static inline void button__f__init(void) {
    ENABLE_PULLUP(BUTTON__F);
}

inline bool button__f__is_on(void) {
    return IS_1(BUTTON__F);
}


#endif
