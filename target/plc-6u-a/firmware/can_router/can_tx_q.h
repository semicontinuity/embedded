#ifndef __CAN_TX_Q_H
#define __CAN_TX_Q_H

#include <stdint.h>

#include "packet.h"
#include "cpu/avr/asm.h"


/*
 *****************************************************************************************************
 * CAN TX Queue
 *****************************************************************************************************
 */

#define CAN_TX_Q_LENGTH	(16)
#define CAN_TX_Q_SIZE 	(CAN_TX_Q_LENGTH * PACKET_Q_STRIDE)

extern   uint8_t can_tx_q[CAN_TX_Q_SIZE] __attribute__((section(".can_tx_q")));
register uint8_t can_tx_q__w_ptr__lo8	asm("r8");
register uint8_t can_tx_q__r_ptr__lo8	asm("r9");
register uint8_t can_tx_q__remaining	asm("r4");	// remaining free space in the queue

/**
 * Constructor.
 * Must use inline assembly, otherwise GCC discards register modifications.
 */
inline void can_tx_q__init(void) {
    CLR	(can_tx_q__w_ptr__lo8);		// aligned to 256 bytes
    CLR	(can_tx_q__r_ptr__lo8);		// aligned to 256 bytes
    uint8_t temp;
    LOAD_CONST8 (temp,	CAN_TX_Q_LENGTH);
    MOV	(can_tx_q__remaining, temp);
}


#endif // __CAN_TX_Q_H