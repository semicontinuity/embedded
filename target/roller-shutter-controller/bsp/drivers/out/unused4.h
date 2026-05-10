#ifndef __DRIVERS__OUT__UNUSED4_H
#define __DRIVERS__OUT__UNUSED4_H

#include "cpu/avr/gpio.h"

inline void unused4__init(void) {
    USE_AS_OUTPUT(UNUSED4);
}

#endif