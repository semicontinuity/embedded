#ifndef __SOFT_USART__TX_H
#define __SOFT_USART__TX_H

#include "cpu/avr/gpio.h"
#include "soft_usart__tx__thread.h"
#include "soft_usart__timer.h"

inline void soft_usart__tx__send(const uint8_t c) {
    soft_usart__tx__thread__data__set(c);
    soft_usart__tx__thread__init();
    soft_usart__timer__start();
}

#endif
