#ifndef __DRIVERS__OUT__UNUSED8_H
#define __DRIVERS__OUT__UNUSED8_H

#include "cpu/avr/gpio.h"

inline void unused8__init(void) {
    USE_AS_OUTPUT(UNUSED8);
}

#endif