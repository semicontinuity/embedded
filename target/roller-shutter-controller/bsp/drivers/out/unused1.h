#ifndef __DRIVERS__OUT__UNUSED1_H
#define __DRIVERS__OUT__UNUSED1_H

#include "cpu/avr/gpio.h"

inline void unused1__init(void) {
    USE_AS_OUTPUT(UNUSED1);
}

#endif