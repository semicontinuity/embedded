#ifndef __SOFT_USART__TX_PIN_H
#define __SOFT_USART__TX_PIN_H

#include "cpu/avr/gpio.h"

inline void soft_usart__tx__pin__init(void) {
    USE_AS_OUTPUT(SOFT_USART__TX);
    OUT_1(SOFT_USART__TX);
}

inline void soft_usart__tx__pin__set(const uint8_t level) {
    if (level)
        OUT_1(SOFT_USART__TX);
    else
        OUT_0(SOFT_USART__TX);
}

#endif
