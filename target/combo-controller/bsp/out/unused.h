#ifndef __OUT__UNUSED_H
#define __OUT__UNUSED_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void out__unused1__init(void) {
    USE_AS_OUTPUT(OUT__UNUSED1);
}

inline void out__unused2__init(void) {
    USE_AS_OUTPUT(OUT__UNUSED2);
}


#endif