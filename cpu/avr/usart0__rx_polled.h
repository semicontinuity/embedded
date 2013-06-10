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
// usart0__in__read
// =============================================================================

inline uint8_t usart0__in__read(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    loop_until_bit_is_set(UCSRA, RXC);
    return UDR;
#else
    #error "Unsupported MCU"
#endif
}


#endif