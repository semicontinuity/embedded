#ifndef __DRIVERS__OUT__UNUSED7_H
#define __DRIVERS__OUT__UNUSED7_H

#include "cpu/avr/gpio.h"

inline void unused7__init(void) {
    USE_AS_OUTPUT(UNUSED7);
}

#endif