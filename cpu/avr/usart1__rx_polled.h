// =============================================================================
// USART1 polling RX
//
// API:
//
// usart1__in__read:
//   Blocking read
// =============================================================================

#ifndef __CPU__AVR__USART1_RX_POLLED_H
#define __CPU__AVR__USART1_RX_POLLED_H

#include <stdint.h>
#include <avr/io.h>


// =============================================================================
// usart0__in__read
// =============================================================================

inline uint8_t usart1__in__read(void) {
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    loop_until_bit_is_set(UCSR1A, RXC1);
    return UDR1;
#else
    #error "Unsupported MCU"
#endif
}


#endif