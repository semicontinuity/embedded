// =============================================================================
// CAN service emulator.
// Handles CAN communications (services incoming requests).
// Extends comm_service__rx.
// =============================================================================
#ifndef __CAN_EMU_SERVICE_H
#define __CAN_EMU_SERVICE_H

#include <avr/interrupt.h>
#include <stdint.h>

#include "cpu/avr/asm.h"
#include "util/bitops.h"

#include "cpu/avr/usart0.h"


#define PACKET_LENGTH	(13)	// (sizeof(mcp251x_message_buffer)) - hardcoded to be usable in inline asm

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

#define USART_RX_THREAD_INTERRUPT	ISR(USART_RX_vect, USART_RX_vect_attrs)
#define usart_rx_thread__enabled__HOST  (UCSR0B)
#define usart_rx_thread__enabled__BIT   (RXCIE0)
DECLARE_BITVAR(usart_rx_thread__enabled, usart_rx_thread__enabled__HOST, usart_rx_thread__enabled__BIT);

register uint8_t *usart_rx_thread__w_ptr        USART_RX_THREAD__W_PTR__REG;
register uint8_t usart_rx_thread__size          USART_RX_THREAD__SIZE__REG;

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_rx_thread__init(void) {
    LOAD_CONST8 (usart_rx_thread__size,	 PACKET_LENGTH);
    LOAD_ADDRESS(usart_rx_thread__w_ptr, comm_service__packet);
}


/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__init(void) {
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();

    usart_rx_thread__init();
}


/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__start(void) {
    usart_rx_thread__enabled__set(1);
}


#endif