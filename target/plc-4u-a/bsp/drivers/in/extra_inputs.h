#ifndef __DRIVERS_IN_EXTRA_INPUTS_H
#define __DRIVERS_IN_EXTRA_INPUTS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void extra_input__a__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__A);
}

inline bool extra_input__a__get(void) {
    return IS_1(EXTRA_INPUT__A);
}


static inline void extra_input__b__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__B);
}

inline bool extra_input__b__get(void) {
    return IS_1(EXTRA_INPUT__B);
}

// Extra input C is for 230V sensor signal. Does not fit into 16 bits for discrete inputs
/*

static inline void extra_input__c__init(void) {
    ENABLE_PULLUP(EXTRA_INPUT__C);
}

inline bool extra_input__c__get(void) {
    return IS_1(EXTRA_INPUT__C);
}

*/

#endif
