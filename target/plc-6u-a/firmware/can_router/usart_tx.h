#ifndef __USART_TX_H
#define __USART_TX_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"


/*
 *****************************************************************************************************
 * USART TX Queue thread:
 * - the only reader of USART TX Queue
 * - implemented with EEPROM_READY interrupt (non-standard use for user interrupt)
 *
 * Property 'usart_tx_q_thread__enabled':
 * - When set, the thread 'usart_tx_q_thread' is constantly scheduled to run.
 * - Is set when (usart_tx_q__remaining < USART_TX_Q_LENGTH), i.e. when the queue is not empty.
 * - Mapped to bit EERIE in EECR, that enables EEPROM_READY interrupt.

 *****************************************************************************************************
 */

#define USART_TX_Q_THREAD_INTERRUPT		ISR(EE_READY_vect, ISR_NAKED)
#define usart_tx_q_thread__enabled__HOST	(EECR)
#define usart_tx_q_thread__enabled__BIT		(EERIE)
DECLARE_BITVAR(usart_tx_q_thread__enabled, usart_tx_q_thread__enabled__HOST, usart_tx_q_thread__enabled__BIT);



/*
 *****************************************************************************************************
 * USART TX thread:
 * - the only reader of USART TX buffer
 * - implemented with USART_UDRE interrupt
 *
 * Property 'usart_tx_thread__enabled':
 * - When set, triggers 'usart_tx_thread'
 * - Mapped to bit UDRIE0 in UCSR0B, that enables USART UDRE interrupt.
 *
 * Property 'usart_tx_thread__r_ptr':
 * - Points to the buffer from where the data must be read.
 * - Thre data transferred must be within bounds of the USART TX queue.
 *
 * Property 'usart_tx_thread__remaining': the number of the bytes remaining to be transferred
 *****************************************************************************************************
 */

#define USART_TX_THREAD_INTERRUPT	ISR(USART_UDRE_vect, ISR_NAKED)
#define usart_tx_thread__enabled__HOST  (UCSR0B)
#define usart_tx_thread__enabled__BIT   (UDRIE0)
DECLARE_BITVAR(usart_tx_thread__enabled, usart_tx_thread__enabled__HOST, usart_tx_thread__enabled__BIT);

register uint8_t usart_tx_thread__r_ptr__lo8	asm("r26");
register uint8_t usart_tx_thread__r_ptr__hi8	asm("r27");
register uint8_t usart_tx_thread__remaining	asm("r18");

#endif // __USART_TX_H