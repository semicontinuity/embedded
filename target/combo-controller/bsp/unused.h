#ifndef __UNUSED_H
#define __UNUSED_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void unused1__init(void) {
    USE_AS_OUTPUT(UNUSED1);
}

inline void unused2__init(void) {
    USE_AS_OUTPUT(UNUSED2);
}

inline void unused3__init(void) {
    USE_AS_OUTPUT(UNUSED3);
}


#endif