#include "device.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "device.h"
#include "usart_tx.h"
#include "usart.h"
#include "packet.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"

/*
 *****************************************************************************************************
 * USART TX Queue thread:
 * Takes packet from the USART TX Queue
 * and creates a task for USART TX thread to actually transfer 
 * - the only reader of USART TX Queue
 * - implemented with EEPROM_READY interrupt (non-standard use for user interrupt)
 *****************************************************************************************************
 */


/**
 * USART TX Queue thread handler.
 * Invoked by the USART TX Queue thread trigger
 * when the USART TX Queue is not empty and USART TX thread is not running.
 * Removes a packet from tail of the queue and ask 'usart_tx_thread' to transmit it to USART.
 */
USART_TX_Q_THREAD_INTERRUPT {
    usart_tx_thread__size = PACKET_LENGTH;
    // Point 'usart_tx_thread__r_ptr' to the tail of the 'usart_tx_q'
    // Higher 8 bits are not changed
    usart_tx_thread__r_ptr__lo8 = usart_tx_q__r_ptr__lo8;

    usart_tx_q__tail__move();
        
    // Spawn 'usart_tx_thread' and yield to it
    usart_tx_thread__enabled__set(1); // triggers binding recomputation.

    RETI();    
}


inline static void usart_tx_thread__on_packet_transferred(void) {    
    // Return control to usart_tx_q_thread, if it has something to do.
    usart_tx_thread__enabled__set(0); // triggers binding recomputation.
}


USART_TX_THREAD_INTERRUPT {
    // usart_tx_thread__r_ptr is in register X.
    XPLUS_TO_USART();

    DEC(usart_tx_thread__size);
    IF_ZERO(usart_tx_thread__on_packet_transferred());
    RETI();    
}



/*
 *****************************************************************************************************
 * Binding: usart_tx_q_thread__enabled = !usart_tx_thread__enabled && !usart_tx_q__empty
 * Triggers USART TX Queue thread, depending on:
 * - the state of USART TX thread (if it is not running, i.e. !usart_tx_thread__enabled
 * - the state of USART TX queue (if it is not empty, i.e. usart_tx_q_size > 0)
 * If both of the following conditions are met, the usart_tx_q_thread is scheduled.
 * usart_tx_q__on_empty is not handled because it is not necessary.
 *****************************************************************************************************
 */

/**
 * Recompute the binding "usart_tx_q_thread__enabled = !usart_tx_thread__enabled && !usart_tx_q__empty"
 * when usart_tx_thread__enabled is set to 0.
 */
INLINE void usart_tx_thread__enabled__on_set_0() {
    if (!usart_tx_q__empty()) usart_tx_q_thread__enabled__set(1);
}

/**
 * Recompute the binding "usart_tx_q_thread__enabled = !usart_tx_thread__enabled && !usart_tx_q__empty"
 * when usart_tx_thread__enabled is set to 1.
 */
INLINE void usart_tx_thread__enabled__on_set_1() {
    usart_tx_q_thread__enabled__set(0);
}

/**
 * Recompute the binding "usart_tx_q_thread__enabled = !usart_tx_thread__enabled && !usart_tx_q__empty"
 * when usart_tx_q is not empty (invoked after every put).
 */
INLINE void usart_tx_q__on_not_empty(void) {
    // compiled to non-optimal code TODO fix
    if (!usart_tx_thread__enabled__is_set()) usart_tx_q_thread__enabled__set(1);
}
