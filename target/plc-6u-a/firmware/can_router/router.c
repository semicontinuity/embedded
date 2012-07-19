#include "device.h"
#include <avr/io.h>

#include "device.h"
#include "debug.h"

#include "router.h"
#include "can_tx.h"
#include "can_tx_q.h"
#include "packet.h"

#include "cpu/avr/asm.h"

/*
 *****************************************************************************************************
 * Routing module
 * Provides function router__process_packet()
 *****************************************************************************************************
 */

/**
 * Route the packet to the CAN TX queue.
 * @param Y register - the pointer to the packet
 */
void route_to_can_tx_q(void) {
    // Everything to slot 0 for now
    if (can_tx_q__remaining > 0) {
        can_tx_q__remaining--;

        // Prepare to copy: set up Z to point to the head of the can_tx_q.
        __asm__ __volatile__ (
            "mov	r30, %0			\n\t"
            "ldi	r31, hi8(can_tx_q)	\n\t"
             :: "r"(can_tx_q__w_ptr__lo8)
        );

/*
        debug__register(r31);
        debug__register(r30);

        debug__register(r8);

        debug__register(r31);
        debug__register(r30);
*/

        // Copy header (5 bytes)
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();

        // Copy data (8 bytes)
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();

        // Move the head pointer,
        // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
        can_tx_q__w_ptr__lo8 += PACKET_Q_STRIDE;

        // Wake up the can_tx_q_thread, if it sleeps
        can_tx_q_thread__enabled__set(1);
    }
}


/**
 * Route the packet
 * @param Y register - the pointer to the packet
 */
void router__process_packet(void) {
    route_to_can_tx_q();
}
