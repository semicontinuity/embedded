// =============================================================================
// Application handler for incoming packets.
// Implements kernel handler API (kernel__out__handle).
// Dispatches the incoming packets, based on the matched filter number.
// Handles TX COMPLETE events.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__endpoint__alarm_client__auth.h"
#include "comm_service__endpoint__alarm_client__state.h"
#include "comm_service__endpoint__sensors.h"
#include "comm_service__endpoint__tty.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 * Handles TX COMPLETE events by setting the corresponding TXB available bits, if they exist.
 */
void comm_service__handle(const uint8_t event, const uint8_t message_type) {
    if (event <= CANP_FILTER__BROADCAST) {
        // Received frame into RXB0 or RXB1
        const uint8_t report = CANP_SLOT_BITS(kernel__frame.header.id);

        if (report == CANP_REPORT__TTY) {
            comm_service__endpoint__tty__handle(message_type);
        }
        else if (report == CANP_REPORT__SENSORS__STATE) {
            comm_service__endpoint__sensors__handle(message_type);
        }
    }
    else if (event == CANP_FILTER__ALARM_SERVER__AUTH && message_type == CANP_MSG_TYPE_VALUE) {
        comm_service__endpoint__alarm_client__auth__handle();
    }
    else if (event == CANP_FILTER__ALARM_SERVER__STATE && message_type == CANP_MSG_TYPE_VALUE) {
        comm_service__endpoint__alarm_client__state__handle();
    }
#if defined(mcp2515__tx__txb1__available__HOST) && defined(mcp2515__tx__txb1__available__BIT)
    else if (event == KERNEL__EVENT__TX1_COMPLETE) {
        mcp2515__tx__txb1__available__set(1);
    }
#endif
#if defined(mcp2515__tx__txb2__available__HOST) && defined(mcp2515__tx__txb2__available__BIT)
    else if (event == KERNEL__EVENT__TX2_COMPLETE) {
        mcp2515__tx__txb2__available__set(1);
    }
#endif
}
