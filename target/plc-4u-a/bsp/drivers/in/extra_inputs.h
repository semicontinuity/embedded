#ifndef __DRIVERS_IN_EXTRA_INPUTS_H
#define __DRIVERS_IN_EXTRA_INPUTS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void extra_input__a__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__A);
}

inline bool extra_input__a__is_on(void) {
    return IS_1(EXTRA_INPUT__A);
}


static inline void extra_input__b__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__B);
}

inline bool extra_input__b__is_on(void) {
    return IS_1(EXTRA_INPUT__B);
}


static inline void extra_input__c__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__C);
}

inline bool extra_input__c__is_on(void) {
    return IS_1(EXTRA_INPUT__C);
}


#endif
