#ifndef __ROUTE_H
#define __ROUTE_H

/**
 * Put the packet to CAN TX queue.
 * @param Y register - the pointer to the packet
 */
void router__put_packet_to_can_tx_q(void) __attribute__((noinline));

#endif // __ROUTE_H