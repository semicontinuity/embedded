#ifndef __SOFT_USART__TX_H
#define __SOFT_USART__TX_H

#include <stdbool.h>
#include "cpu/avr/gpio.h"
#include "soft_usart__tx__thread.h"
#include "soft_usart__timer.h"

bool soft_usart__tx__is_busy(void) {
    return soft_usart__tx__thread__is_runnable();
}

void soft_usart__tx__send(const uint8_t c) {
    soft_usart__tx__thread__data__set(c);
    soft_usart__tx__thread__init();
    soft_usart__timer__start();
}

void soft_usart__tx__write(const uint8_t c) {
    while (soft_usart__tx__is_busy());
    soft_usart__tx__send(c);
}


#endif
