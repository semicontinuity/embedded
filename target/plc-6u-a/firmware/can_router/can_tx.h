#ifndef __CAN_TX_H
#define __CAN_TX_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"
#include "can_tx_q.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/bitops.h"


/*
 *****************************************************************************************************
 * CAN TX Queue thread:
 * - the only reader of the CAN TX Queue
 * - implemented with SPM_READY interrupt (non-standard use; user-triggered interrupt)
 *
 * Property 'can_tx_q_thread__enabled':
 * - When set, the thread 'can_tx_q_thread' is constantly scheduled to run.
 * - Is set when (can_tx_q__remaining < CAN_TX_Q_LENGTH), i.e. when the queue is not empty.
 * - Mapped to bit SPMIE in EECR, that enables SPM_READY interrupt.

 *****************************************************************************************************
 */

#define CAN_TX_Q_THREAD_INTERRUPT	ISR(SPM_READY_vect, ISR_NAKED)
#define can_tx_q_thread__enabled__HOST	(SPMCSR)
#define can_tx_q_thread__enabled__BIT	(SPMIE)
DECLARE_BITVAR(can_tx_q_thread__enabled, SPMCSR, SPMIE)

#endif // __CAN_TX_H