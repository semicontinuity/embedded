// =============================================================================
// Kernel, handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================
#ifndef __KERNEL__RX__HANDLER_H
#define __kERNEL__RX__HANDLER_H

#include <stdint.h>
#include "kernel.h"
#include "kernel__rx__handler__spi.h"
#include "kernel__admin.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"

/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
static inline void kernel__rx__handle(const uint8_t filter) {
    // use CANP_IS_RESPONSE
    uint8_t supported = 0;
    const uint8_t owner_bits = CANP_OWNER_BITS(comm_service__packet.header.id);
    const uint8_t rtr_bits = CANP_RTR_BITS(comm_service__packet.header);

    if (rtr_bits) {
        if (owner_bits) supported = 1;
    }
    else {
        if (!owner_bits) supported = 1;
    }
    // possible to send error response...
    if (!supported) return;



    if (filter == CANP_FILTER__ADMIN) {
        if (CANP_REQUEST_PUT(rtr_bits))  {
            kernel__admin__handle();
        }
    }
    else {
        kernel__rx__handle_delegate(filter, rtr_bits);
    }
}

#endif