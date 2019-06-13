#ifndef __DRIVERS__OUT__UNUSED0_H
#define __DRIVERS__OUT__UNUSED0_H

#include "cpu/avr/gpio.h"

inline void unused0__init(void) {
    USE_AS_OUTPUT(OUT__UNUSED0);
}

#endif