#ifndef __DRIVERS__OUT__UNUSED11_H
#define __DRIVERS__OUT__UNUSED11_H

#include "cpu/avr/gpio.h"

inline void unused11__init(void) {
    USE_AS_OUTPUT(UNUSED11);
}

#endif