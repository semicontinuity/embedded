// =============================================================================
// Application handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler__spi.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__endpoint__alarm__auth.h"
#include "comm_service__endpoint__alarm__state.h"
#include "comm_service__endpoint__io.h"
#include "comm_service__endpoint__sensors.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
void comm_service__handle(const uint8_t event, const uint8_t message_type) {
    if (event <= CANP_FILTER__BROADCAST) {
        // Received frame into RXB0 or RXB1
        const uint8_t report = CANP_SLOT_BITS(kernel__frame.header.id);

        if (report >= CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE && report <= CANP_REPORT__SIREN2__VALUE) {
            comm_service__endpoint__io__handle_output(message_type, report);
        }
        else if (report == CANP_REPORT__WATER_LEAK_SENSORS_SCANNER__VALUE || report == CANP_REPORT__MOTION_SENSORS_SCANNER__VALUE) {
            comm_service__endpoint__io__handle_input(message_type, report);
        }
        else if (report == CANP_REPORT__ALARM__AUTH) {
            comm_service__endpoint__alarm__auth__handle(message_type);
        }
        else if (report == CANP_REPORT__ALARM__STATE) {
            comm_service__endpoint__alarm__state__handle(message_type);
        }
    }
    else if (event == CANP_REPORT__SENSORS__STATE && message_type == CANP_MSG_TYPE_VALUE) {
        comm_service__endpoint__sensors__handle_value();
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
