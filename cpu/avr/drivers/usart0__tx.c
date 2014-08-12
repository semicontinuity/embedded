// =============================================================================
// Generic USART0 interrupt-based driver for transmission.
// =============================================================================

#include "cpu/avr/drivers/usart0__tx.h"

#include "cpu/avr/usart0.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


void usart0__tx__start(void) {
    usart0__tx__enabled__set(1);    
    usart0__tx__data_register_empty__interrupt__enabled__set(1);
}


void usart0__tx__stop(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(0);
    usart0__tx__enabled__set(0);
}


#ifdef usart0__tx__data_register_empty__interrupt__NAKED
#define usart0__tx__data_register_empty__interrupt__ATTR_NAKED ISR_NAKED
#else
#define usart0__tx__data_register_empty__interrupt__ATTR_NAKED
#endif

ISR(usart0__tx__data_register_empty__interrupt__VECTOR, usart0__tx__data_register_empty__interrupt__ATTRS usart0__tx__data_register_empty__interrupt__ATTR_NAKED) {

#ifndef USART0__TX__DATA__REG
    uint8_t usart0__tx__data;
#endif

    if (usart0__tx__has_next()) {
        usart0__tx__data = usart0__tx__next();
        usart0__putc(usart0__tx__data);
    }
    else {
        usart0__tx__on_done();
    }

#ifdef usart0__tx__data_register_empty__interrupt__NAKED
    reti();
#endif
}


