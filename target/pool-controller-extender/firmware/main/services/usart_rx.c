// =============================================================================
// USART receiver driver.
// =============================================================================

#include "services/usart_rx.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/usart0.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


void usart_rx__start(void) {
    usart0__rx__enabled__set(1);    
    usart0__rx__complete__interrupt__enabled__set(1);
}


void usart_rx__stop(void) {
    usart0__rx__complete__interrupt__enabled__set(0);
    usart0__rx__enabled__set(0);
}


ISR(usart0__rx__complete__interrupt__VECTOR, usart0__rx__complete__interrupt__ATTRS) {

#ifndef USART_RX__DATA__REG
    uint8_t usart_rx__data;
#endif

    USART0__GETC(usart_rx__data);
    usart_rx__on_data(usart_rx__data);
}
