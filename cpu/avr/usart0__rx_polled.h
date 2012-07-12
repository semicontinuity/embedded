// =============================================================================
// USART0 polling RX
//
// API:
//
// usart_in__read:
//   Blocking read
// =============================================================================

#ifndef __CPU__AVR__USART0_RX_POLLING_H
#define __CPU__AVR__USART0_RX_POLLING_H

#include "device.h"

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>


// =============================================================================
// usart__in__read
// =============================================================================

inline static char usart__in__read(void) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
#elif defined(__AVR_ATmega8__)
    loop_until_bit_is_set(UCSRA, RXC);
    return UDR;
#else
    #error "Unsupported MCU"
#endif
}


#endif