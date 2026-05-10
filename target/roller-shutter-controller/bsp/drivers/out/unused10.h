#ifndef __DRIVERS__OUT__UNUSED10_H
#define __DRIVERS__OUT__UNUSED10_H

#include "cpu/avr/gpio.h"

inline void unused10__init(void) {
    USE_AS_OUTPUT(UNUSED10);
}

#endif