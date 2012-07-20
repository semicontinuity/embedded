#ifndef __CAN_TX_Q_H
#define __CAN_TX_Q_H

#include <stdbool.h>
#include <stdint.h>

#include "packet.h"
#include "cpu/avr/asm.h"


/*
 *****************************************************************************************************
 * CAN TX Queue
 *****************************************************************************************************
 */

#define CAN_TX_Q_LENGTH         (16)
#define CAN_TX_Q_SIZE_BYTES     (CAN_TX_Q_LENGTH * PACKET_Q_STRIDE)

extern   uint8_t can_tx_q[CAN_TX_Q_SIZE_BYTES] __attribute__((section(".can_tx_q")));
register uint8_t can_tx_q__w_ptr__lo8   asm("r8");
register uint8_t can_tx_q__r_ptr__lo8   asm("r9");
register uint8_t can_tx_q__size         asm("r4");	// the number of packets in the queue

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void can_tx_q__init(void) {
    CLR	(can_tx_q__w_ptr__lo8);		// aligned to 256 bytes, so lower byte is 0 initially
    CLR	(can_tx_q__r_ptr__lo8);		// aligned to 256 bytes, so lower byte is 0 initially
    CLR	(can_tx_q__size);
}


inline bool can_tx_q__empty(void) {
    return can_tx_q__size == 0;
}

inline bool can_tx_q__full(void) {
    return can_tx_q__size == CAN_TX_Q_LENGTH;
}


/**
 * Moves the head pointer (the element the head is logically removed).
 * Adjusts the queue size and the head (write) pointer.
 */
inline void can_tx_q__head__move(void) {
    can_tx_q__size++;
    // Advances lower 8 bits of the head (write) pointer.
    // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
    can_tx_q__w_ptr__lo8 += PACKET_Q_STRIDE;
}


/**
 * Copy the head pointer to the z register
 */
inline void can_tx_q__head__to_z(void) {
    // Prepare to copy: set up Z to point to the head of the usart_tx_q.
    __asm__ __volatile__ (
        "mov	r30, %0			\n\t"
        "ldi	r31, hi8(can_tx_q)	\n\t"
        :: "r"(can_tx_q__w_ptr__lo8)
    );
}


/**
 * Moves the tail pointer (the element the tail is logically removed).
 * Adjusts the queue size and the tail (read) pointer.
 */
inline void can_tx_q__tail__move(void) {
    can_tx_q__size--;
    // Advances lower 8 bits of the tail (read) pointer.
    // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
    can_tx_q__r_ptr__lo8 += PACKET_Q_STRIDE;
}


/**
 * Copy the tail pointer to the z register
 */
inline void can_tx_q__tail__to_z(void) {
    // Prepare to copy: set up Z to point to the head of the usart_tx_q.
    __asm__ __volatile__ (
        "mov	r30, %0			\n\t"
        "ldi	r31, hi8(can_tx_q)	\n\t"
        :: "r"(can_tx_q__r_ptr__lo8)
    );
}


/**
 * Puts the packet to the CAN TX queue.
 * @param Y register - the pointer to the packet
 */
void can_tx_q__put(void);


/**
 * Invoked after the put to the queue.
 * Implement in the application code.
 */
INLINE void can_tx_q__on_not_empty(void);

/**
 * Put the packet to the queue, if it is not full.
 * The function f is invoked to actually write data to the queue (with Z register pointing into the queue)
 */
#define can_tx_q__put_if_not_full(f) do {     \
    if (!can_tx_q__full()) {                  \
        can_tx_q__head__to_z();               \
        f;                                    \
        can_tx_q__head__move();               \
        can_tx_q__on_not_empty();             \
    }                                         \
} while(0)


#endif // __CAN_TX_Q_H