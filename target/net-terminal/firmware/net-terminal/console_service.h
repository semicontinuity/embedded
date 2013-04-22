#ifndef __CONSOLE_SERVICE_H
#define __CONSOLE_SERVICE_H

#include "cpu/avr/usart0.h"


inline void console_service__init(void) {
    usart0__rate__set(USART_BAUD_RATE);
    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();
}

void console_service__run(void);

#endif