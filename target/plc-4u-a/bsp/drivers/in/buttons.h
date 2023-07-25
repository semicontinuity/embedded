#ifndef __DRIVERS_IN_BUTTONS_H
#define __DRIVERS_IN_BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void button__a__init(void) {
    ENABLE_PULLUP(BUTTON__A);
}

inline bool button__a__get(void) {
    return IS_1(BUTTON__A);
}


static inline void button__b__init(void) {
    ENABLE_PULLUP(BUTTON__B);
}

inline bool button__b__get(void) {
    return IS_1(BUTTON__B);
}

#ifdef __AVR_ATmega16__

static inline void button__c__init(void) {
    ENABLE_PULLUP(BUTTON__C);
}

inline bool button__c__get(void) {
    return IS_1(BUTTON__C);
}


static inline void button__d__init(void) {
    ENABLE_PULLUP(BUTTON__D);
}

inline bool button__d__get(void) {
    return IS_1(BUTTON__D);
}

#else


static inline void button__c__init(void) {
}

inline bool button__c__get(void) {
    return true;
}


static inline void button__d__init(void) {
}

inline bool button__d__get(void) {
    return true;
}

#endif

static inline void button__e__init(void) {
    ENABLE_PULLUP(BUTTON__E);
}

inline bool button__e__get(void) {
    return IS_1(BUTTON__E);
}


static inline void button__f__init(void) {
    ENABLE_PULLUP(BUTTON__F);
}

inline bool button__f__get(void) {
    return IS_1(BUTTON__F);
}


#endif
