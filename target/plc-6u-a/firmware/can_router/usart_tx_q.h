#ifndef __USART_TX_Q_H
#define __USART_TX_Q_H

#include <stdbool.h>
#include <stdint.h>

#include "usart_tx.h"
#include "packet.h"

#include "cpu/avr/asm.h"


/*
 *****************************************************************************************************
 * USART TX Queue
 *****************************************************************************************************
 */

#define USART_TX_Q_LENGTH	(16)
#define USART_TX_Q_SIZE 	(USART_TX_Q_LENGTH * PACKET_Q_STRIDE)

extern   uint8_t usart_tx_q[USART_TX_Q_SIZE] __attribute__((section(".usart_tx_q")));
register uint8_t usart_tx_q__w_ptr__lo8	asm("r16");
register uint8_t usart_tx_q__r_ptr__lo8	asm("r17");
register  int8_t usart_tx_q__remaining	asm("r21");	// remaining free space in the queue

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_tx_q__init(void) {
    LOAD_ADDRESS_LO8(usart_tx_q__w_ptr__lo8, usart_tx_q);
    LOAD_ADDRESS_LO8(usart_tx_q__r_ptr__lo8, usart_tx_q);
    LOAD_CONST8(usart_tx_q__remaining, USART_TX_Q_LENGTH);
}


inline bool usart_tx_q__not_empty(void) {
    return usart_tx_q__remaining > 0;
}


inline void usart_tx_q__write__begin(void) {
    usart_tx_q__remaining--;

    // Prepare to copy: set up Z to point to the head of the usart_tx_q.
    __asm__ __volatile__ (
        "mov	r30, %0			\n\t"
        "ldi	r31, hi8(usart_tx_q)	\n\t"
        :: "r"(usart_tx_q__w_ptr__lo8)
    );

    // Move head pointer
    // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
    usart_tx_q__w_ptr__lo8 += PACKET_Q_STRIDE;
}


inline void usart_tx_q__write__end(void) {
    // Wake up usart_tx_q_thread, if it sleeps
    // HARDCODED behavior.
    usart_tx_q_thread__enabled__set(1);
}


#endif // __USART_TX_Q_H