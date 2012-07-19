#include "device.h"
#include <avr/io.h>

#include "device.h"
#include "debug.h"

#include "router.h"
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
 * Route the packet
 * @param Y register - the pointer to the packet
 */
void router__process_packet(void) {
    can_tx_q__put();
}
