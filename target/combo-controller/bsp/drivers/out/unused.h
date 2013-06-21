#ifndef __DRIVERS__OUT__UNUSED_H
#define __DRIVERS__OUT__UNUSED_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void unused2__init(void) {
    USE_AS_OUTPUT(OUT__UNUSED2);
}


#endif