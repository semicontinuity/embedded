#ifndef __DRIVERS__OUT__UNUSED5_H
#define __DRIVERS__OUT__UNUSED5_H

#include "cpu/avr/gpio.h"

inline void unused5__init(void) {
    USE_AS_OUTPUT(UNUSED5);
}

#endif