#ifndef __DRIVERS__OUT__UNUSED9_H
#define __DRIVERS__OUT__UNUSED9_H

#include "cpu/avr/gpio.h"

inline void unused9__init(void) {
    USE_AS_OUTPUT(UNUSED9);
}

#endif