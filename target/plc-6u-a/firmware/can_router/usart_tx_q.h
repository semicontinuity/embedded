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
#define USART_TX_Q_SIZE_BYTES 	(USART_TX_Q_LENGTH * PACKET_Q_STRIDE)

extern   uint8_t usart_tx_q[USART_TX_Q_SIZE_BYTES] __attribute__((section(".usart_tx_q")));
register uint8_t usart_tx_q__w_ptr__lo8 asm("r16");
register uint8_t usart_tx_q__r_ptr__lo8 asm("r17");
register uint8_t usart_tx_q__size       asm("r21");	// the number of packets in the queue

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void usart_tx_q__init(void) {
    LOAD_ADDRESS_LO8(usart_tx_q__w_ptr__lo8, usart_tx_q);
    LOAD_ADDRESS_LO8(usart_tx_q__r_ptr__lo8, usart_tx_q);
    CLR(usart_tx_q__size);
}


inline bool usart_tx_q__empty(void) {
    return usart_tx_q__size == 0;
}

inline bool usart_tx_q__full(void) {
    return usart_tx_q__size == USART_TX_Q_LENGTH;
}


/**
 * Moves the head pointer (the element the head is logically removed).
 * Adjusts the queue size and the head (write) pointer.
 */
inline void usart_tx_q__head__move(void) {
    usart_tx_q__size++;
    // Advances lower 8 bits of the head (write) pointer.
    // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
    usart_tx_q__w_ptr__lo8 += PACKET_Q_STRIDE;
}


/**
 * Copy the head pointer to the z register
 */
inline void usart_tx_q__head__to_z(void) {
    // Prepare to copy: set up Z to point to the head of the usart_tx_q.
    __asm__ __volatile__ (
        "mov	r30, %0			\n\t"
        "ldi	r31, hi8(usart_tx_q)	\n\t"
        :: "r"(usart_tx_q__w_ptr__lo8)
    );
}


/**
 * Moves the tail pointer (the element the tail is logically removed).
 * Adjusts the queue size and the tail (read) pointer.
 */
inline void usart_tx_q__tail__move(void) {
    usart_tx_q__size--;
    // Advances lower 8 bits of the tail (read) pointer.
    // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
    usart_tx_q__r_ptr__lo8 += PACKET_Q_STRIDE;
}

/**
 * Copy the tail pointer to the z register
 */
inline void usart_tx_q__tail__to_z(void) {
    // Prepare to copy: set up Z to point to the head of the usart_tx_q.
    __asm__ __volatile__ (
        "mov	r30, %0			\n\t"
        "ldi	r31, hi8(usart_tx_q)	\n\t"
        :: "r"(usart_tx_q__r_ptr__lo8)
    );
}

/**
 * Invoked after the put to the queue.
 * Implement in the application code.
 */
INLINE void usart_tx_q__on_not_empty(void);

/**
 * Put the packet to the queue, if it is not full.
 * The function f is invoked to actually write data to the queue (with Z register pointing into the queue)
 */
#define usart_tx_q__put_if_not_full(f) do {     \
    if (!usart_tx_q__full()) {                  \
        usart_tx_q__head__to_z();               \
        f;                                      \
        usart_tx_q__head__move();               \
        usart_tx_q__on_not_empty();             \
    }                                           \
} while(0)


#endif // __USART_TX_Q_H