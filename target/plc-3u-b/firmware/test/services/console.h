#ifndef __SERVICES__CONSOLE_H
#define __SERVICES__CONSOLE_H

#include "cpu/avr/usart0.h"


inline void console__init(void) {
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}

INLINE void console__run(void);

#endif