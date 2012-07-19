#ifndef __USART_RX_H
#define __USART_RX_H

#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"
#include "usart_rx_buffer.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"


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
 * Property 'usart_rx_thread__remaining': the number of the bytes remaining to be transferred
 *
 *****************************************************************************************************
 */

#define USART_RX_THREAD_INTERRUPT	ISR(USART_RX_vect, ISR_NAKED)
#define usart_rx_thread__enabled__HOST  (UCSR0B)
#define usart_rx_thread__enabled__BIT   (RXCIE0)
DECLARE_BITVAR(usart_rx_thread__enabled, usart_rx_thread__enabled__HOST, usart_rx_thread__enabled__BIT);

register uint8_t *usart_rx_thread__w_ptr	asm("r28");
register uint8_t usart_rx_thread__remaining	asm("r19");

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_rx_thread__init(void) {
    LOAD_CONST8 (usart_rx_thread__remaining,	PACKET_LENGTH);
    LOAD_ADDRESS(usart_rx_thread__w_ptr,	usart_rx_buffer);
}


#endif // __USART_RX_H