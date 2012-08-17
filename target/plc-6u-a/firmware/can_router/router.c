#include <avr/io.h>

#include "debug.h"

#include "router.h"
#include "can_tx_q.h"
#include "packet.h"

#include "cpu/avr/asm.h"

/*
 *****************************************************************************************************
 * Routing module
 *****************************************************************************************************
 */


/**
 * Put the packet to CAN TX queue.
 * @param Y register - the pointer to the packet
 */
void router__put_packet_to_can_tx_q(void) {
    can_tx_q__put_if_not_full(packet__copy());
}
