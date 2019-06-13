#ifndef __DRIVERS__OUT__UNUSED3_H
#define __DRIVERS__OUT__UNUSED3_H

#include "cpu/avr/gpio.h"

inline void unused3__init(void) {
    USE_AS_OUTPUT(OUT__UNUSED3);
}

#endif