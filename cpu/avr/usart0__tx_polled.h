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

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>


// =============================================================================
// usart0__out__write
// =============================================================================

inline void usart0__out__write(char c) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
#else
    #error "Unsupported MCU"
#endif
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