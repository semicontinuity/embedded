// =============================================================================
// Communications service, handler.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================
#ifndef __COMM_SERVICE_HANDLER_H
#define __COMM_SERVICE_HANDLER_H

#include <stdint.h>
#include "comm_service.h"
#include "comm_service__admin.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"

#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
static inline void comm_service__rx__put(const uint8_t filter) {
    uint8_t supported = 0;
    const uint8_t owner_bits = CANP_OWNER_BITS(comm_service__packet.header.id);
    const uint8_t rtr_bits = CANP_RTR_BITS(comm_service__packet.header);
    if (rtr_bits) {
        if (owner_bits) supported = 1;
    }
    else {
        if (!owner_bits) supported = 1;
    }

    // possible to send error response
    if (!supported) return;

    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__descriptor_memory__handle(rtr_bits);
        break;
    case CANP_FILTER__ADMIN:
        comm_service__admin__handle(rtr_bits);
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST:
        switch (CANP_SLOT_BITS(comm_service__packet.header.id)) {
        case CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE:
            comm_service__motor_controller__motor_mode__handle(rtr_bits);
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__CONTROL:
            comm_service__motor_controller__control__handle(rtr_bits);
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__STATUS:
            comm_service__motor_controller__status__handle(rtr_bits);
            break;
        case CANP_REPORT__BUTTONS_SCANNER__STATUS:
            comm_service__buttons_scanner__status__handle(rtr_bits);
            break;
        }
    }
}

#endif