#ifndef __CONSOLE_SERVICE_H
#define __CONSOLE_SERVICE_H

#include "device.h"
#include "cpu/avr/usart0.h"

static void console_service__init(void) {
//    CONFIGURE_AS_OUTPUT(TX);
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();
}

void console_service__run(void);

#endif