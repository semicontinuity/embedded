// =============================================================================
// Application handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__rx__handler__spi.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"

#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
void comm_service__handler__handle(const uint8_t filter, const uint8_t is_get) {
    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__descriptor_memory__handle(is_get);
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST:
        switch (CANP_SLOT_BITS(kernel__frame.header.id)) {
        case CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE:
            comm_service__motor_controller__motor_mode__handle(is_get);
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__CONTROL:
            comm_service__motor_controller__control__handle(is_get);
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__STATUS:
            comm_service__motor_controller__status__handle(is_get);
            break;
        case CANP_REPORT__BUTTONS_SCANNER__STATUS:
            comm_service__buttons_scanner__status__handle(is_get);
            break;
        }
    }
}
