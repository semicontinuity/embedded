#ifndef __DRIVERS__OUT__UNUSED6_H
#define __DRIVERS__OUT__UNUSED6_H

#include "cpu/avr/gpio.h"

inline void unused6__init(void) {
    USE_AS_OUTPUT(UNUSED6);
}

#endif