// =============================================================================
// USART0 polling RX
//
// API:
//
// usart0__in__read:
//   Blocking read
// =============================================================================

#ifndef __CPU__AVR__USART0_RX_POLLED_H
#define __CPU__AVR__USART0_RX_POLLED_H

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>


// =============================================================================
// usart0__in__wait
// =============================================================================

inline void usart0__in__wait(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    loop_until_bit_is_set(UCSR0A, RXC0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    loop_until_bit_is_set(UCSRA, RXC);
#elif defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    loop_until_bit_is_set(UCSR1A, RXC1);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__in__read
// =============================================================================

inline uint8_t usart0__in__read(void) {
    usart0__in__wait();
    return usart0__getc();
}


#endif