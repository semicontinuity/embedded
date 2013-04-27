// =============================================================================
// Application handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler__spi.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__endpoint__alarm__state.h"
#include "comm_service__endpoint__alarm__auth.h"
#include "comm_service__endpoint__io.h"

#include CAN_H


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
void comm_service__handle(const uint8_t event, const uint8_t message_type) {
    if (event == CANP_FILTER__USER || event == CANP_FILTER__USER_MCAST) {
        const uint8_t report = CANP_SLOT_BITS(kernel__frame.header.id);

        if (report >= CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE && report <= CANP_REPORT__SIREN2__VALUE) {
            comm_service__endpoint__io__handle_output(message_type, report);
        }
        else if (report == CANP_REPORT__WATER_LEAK_SENSORS_SCANNER__VALUE) {
            comm_service__endpoint__io__handle_input(message_type, report);
        }
        else if (report == CANP_REPORT__ALARM__AUTH) {
            comm_service__endpoint__alarm__auth__handle(message_type);
        }
        else if (report == CANP_REPORT__ALARM__STATE) {
            comm_service__endpoint__alarm__state__handle(message_type);
        }
    }
    else if (event == KERNEL__EVENT__TX1_COMPLETE) {
        can__txb1__available__set(1);
    }
}
