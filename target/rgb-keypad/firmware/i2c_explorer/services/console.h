#ifndef __SERVICES__CONSOLE_H
#define __SERVICES__CONSOLE_H

#include "cpu/avr/usart0.h"


void console__init(void) {
    usart0__init();
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}

void console__start(void);

void console__run(void);


#endif