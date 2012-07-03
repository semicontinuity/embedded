#ifndef __USART_TX_Q_H
#define __USART_TX_Q_H

#include <stdint.h>

#include "packet.h"
#include "cpu/avr/asm.h"


/*
 *****************************************************************************************************
 * USART TX Queue
 *****************************************************************************************************
 */

#define USART_TX_Q_LENGTH	(16)
#define USART_TX_Q_SIZE 	(USART_TX_Q_LENGTH * PACKET_Q_STRIDE)

volatile uint8_t usart_tx_q[USART_TX_Q_SIZE];
register uint8_t usart_tx_q__w_ptr__lo8	asm("r16");
register uint8_t *usart_tx_q__w_ptr	asm("r16");
register uint8_t usart_tx_q__r_ptr__lo8	asm("r17");
register uint8_t usart_tx_q__remaining	asm("r21");	// remaining free space in the queue

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_tx_q__init(void) {
    LOAD_ADDRESS_LO8(usart_tx_q__w_ptr__lo8, usart_tx_q);
    LOAD_ADDRESS_LO8(usart_tx_q__r_ptr__lo8, usart_tx_q);
    LOAD_CONST8(usart_tx_q__remaining, USART_TX_Q_LENGTH);
}


#endif // __USART_TX_Q_H