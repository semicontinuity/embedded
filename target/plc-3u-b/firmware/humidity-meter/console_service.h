#ifndef __CONSOLE_SERVICE_H
#define __CONSOLE_SERVICE_H

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


inline void console_service__init(void) {
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}

void console_service__run(void);

#endif