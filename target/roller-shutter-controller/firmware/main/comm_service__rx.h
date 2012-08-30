// =============================================================================
// Communications service, receiver.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================
#ifndef __COMM_SERVICE_RX_H
#define __COMM_SERVICE_RX_H

#include <stdint.h>
#include "comm_service.h"
#include "comm_service__admin.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"

#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


/**
 * Initializes the service.
 * Must be provided by implementation.
 */
inline static /*abstract */ void comm_service__rx__init(void);

/**
 * Starts the service.
 * Must be provided by implementation.
 */
inline static /*abstract */ void comm_service__rx__start(void);


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
static inline void comm_service__rx__put(const uint8_t filter) {
    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__descriptor_memory__handle();
        break;
    case CANP_FILTER__ADMIN:
        comm_service__admin__handle();
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST:
        switch (CANP_SLOT_BITS(comm_service__buffer.header.id)) {
        case CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE:
            comm_service__motor_controller__motor_mode__handle();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__CONTROL:
            comm_service__motor_controller__control__handle();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__STATUS:
            comm_service__motor_controller__status__handle();
            break;
        case CANP_REPORT__BUTTONS_SCANNER__STATUS:
            comm_service__buttons_scanner__status__handle();
            break;
        }
    }
}

#endif