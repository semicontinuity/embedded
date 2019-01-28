// =============================================================================
// Kernel, handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================
#ifndef __KERNEL__RX__HANDLER_H
#define __kERNEL__RX__HANDLER_H

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler.h"
#include "kernel__admin.h"
#include "cpu/avr/drivers/net/can/mcp251x/ucan.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
static inline void kernel__rx__handle(const uint8_t filter) {
    const uint8_t message_type = UCAN_MSG_TYPE(kernel__frame.header);

    if (UCAN_PORT_BITS(kernel__frame.header.id) >= UCAN__PF__SYSTEM) {
        if (message_type == UCAN_MSG_TYPE_POST) {
            kernel__admin__handle();
        }
    }
    else {
        kernel__out__handle(filter, message_type);
    }
}

#endif