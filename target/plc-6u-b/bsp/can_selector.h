#ifndef __CAN_SELECTOR_H
#define __CAN_SELECTOR_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"


static inline void can_selector__init(void) {
    USE_AS_OUTPUT(SLOT0_SELECT);
    OUT_1(SLOT0_SELECT);
}

#define can_selector__run(op) do {\
    OUT_0(SLOT0_SELECT);\
    op;\
    OUT_1(SLOT0_SELECT);\
} while(0)


#endif