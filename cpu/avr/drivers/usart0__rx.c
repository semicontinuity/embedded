// =============================================================================
// USART0 receiver driver.
// =============================================================================

#include "cpu/avr/drivers/usart0__rx.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/usart0.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


void usart0__rx__start(void) {
    usart0__rx__enabled__set(1);    
    usart0__rx__complete__interrupt__enabled__set(1);
}


void usart0__rx__stop(void) {
    usart0__rx__complete__interrupt__enabled__set(0);
    usart0__rx__enabled__set(0);
}


#ifdef usart0__rx__complete__interrupt__NAKED
#define usart0__rx__complete__interrupt__ATTR_NAKED ISR_NAKED
#else
#define usart0__rx__complete__interrupt__ATTR_NAKED
#endif

ISR(usart0__rx__complete__interrupt__VECTOR, usart0__rx__complete__interrupt__ATTRS usart0__rx__complete__interrupt__ATTR_NAKED) {

#ifndef USART0__RX__DATA__REG
    uint8_t usart0__rx__data;
#endif

    usart0__rx__data = usart0__getc();
    usart0__rx__on_data(usart0__rx__data);

#ifdef usart0__rx__complete__interrupt__NAKED
    reti();
#endif
}
