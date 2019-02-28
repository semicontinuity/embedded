// =============================================================================
// USI USART.
// =============================================================================


#ifndef __USI_USART__TX_H
#define __USI_USART__TX_H

#include <stdint.h>
#include <avr/io.h>


inline static void usi_usart__tx__init(void) {
    DDRB |= (1<<1); // B1 output
    PORTB |= (1<<1); // B1=1
}

#endif