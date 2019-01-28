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

#include "cpu/avr/usart0.h"
#include <stdint.h>
#include <avr/io.h>


// =============================================================================
// usart0__in__wait
// =============================================================================

inline void usart0__in__wait(void) {
    loop_until_bit_is_set(usart0__rx__complete__value__HOST, usart0__rx__complete__value__BIT);
}


// =============================================================================
// usart0__in__read
// =============================================================================

inline uint8_t usart0__in__read(void) {
    usart0__in__wait();
    return usart0__getc();
}


#endif