// =============================================================================
// USART0 TX API that uses polling.
//
// API:
//
// usart0__out__write:
//   Blocks while USART s transmitting, then writes another byte to USART.
// =============================================================================

#ifndef __CPU__AVR__USART0_TX_POLLED_H
#define __CPU__AVR__USART0_TX_POLLED_H

#include "cpu/avr/usart0.h"
#include <stdint.h>
#include <avr/io.h>


// =============================================================================
// usart0__out__wait
// =============================================================================

inline void usart0__out__wait(void) {
    loop_until_bit_is_set(usart0__tx__data_register_empty__value__HOST, usart0__tx__data_register_empty__value__BIT);
}


// =============================================================================
// usart0__out__write
// =============================================================================

inline void usart0__out__write(char c) {
    usart0__out__wait();
    usart0__putc(c);
}


// =============================================================================
// usart0__out__send
// =============================================================================

inline void usart0__out__send(const char *data, uint8_t count) {
    // synchronously
    do {
        // do not inline 'b' -compiler will produce less optimal code.
        char b = *data++;
        usart0__out__write(b);
    }
    while (--count > 0);
}


#endif