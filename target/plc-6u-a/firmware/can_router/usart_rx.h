#ifndef __USART_RX_H
#define __USART_RX_H

#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/usart0.h"
#include "util/bitops.h"


extern uint8_t usart_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));

/*
 *****************************************************************************************************
 * USART RX Thread, implemented with USART RX interrupt.
 *
 * Property 'usart_rx_thread__enabled':
 * - When set, USART RX interrupt is enabled.
 * - Mapped to bit RXCIE0 in UCSR0B, that enables USART RX interrupt.
 *
 * Property 'usart_rx_thread__w_ptr':
 * - Points to the buffer where the data must be written.
 * - The data transferred must be within bounds of the USART TX queue.
 *
 * Property 'usart_rx_thread__size': the number of the bytes in the buffer (to be transferred)
 *
 *****************************************************************************************************
 */

#define USART_RX_THREAD_INTERRUPT	ISR(usart0__rx__complete__interrupt__VECTOR, ISR_NAKED)
DEFINE_BITVAR(usart_rx_thread__enabled, usart0__rx__complete__interrupt__enabled__HOST, usart0__rx__complete__interrupt__enabled__BIT);

register uint8_t *usart_rx_thread__w_ptr        asm("r28");
register uint8_t usart_rx_thread__size          asm("r19");

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_rx_thread__init(void) {
    LOAD_CONST8 (usart_rx_thread__size,	 PACKET_LENGTH);
    LOAD_ADDRESS(usart_rx_thread__w_ptr, usart_rx_buffer);
}


#endif // __USART_RX_H