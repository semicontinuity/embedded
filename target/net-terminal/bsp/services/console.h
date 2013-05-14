#ifndef __SERVICES__CONSOLE_H
#define __SERVICES__CONSOLE_H

#include "cpu/avr/usart0.h"


inline void console__init(void) {
    usart0__rate__set(USART_BAUD_RATE);
    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();
}

INLINE void console__run(void);

#endif