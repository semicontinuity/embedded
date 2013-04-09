// =============================================================================
// Application handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__rx__handler__spi.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__endpoint__gpio.h"
#include "comm_service__endpoint__water_valve_controller.h"

#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
void comm_service__rx__handle(const uint8_t filter, const uint8_t is_get) {
    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__descriptor_memory__handle(is_get);
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST: {
            uint8_t slot = CANP_SLOT_BITS(kernel__frame.header.id);
            if (slot <= CANP_REPORT__GPIO__PORT_CNF3) 
                comm_service__endpoint__gpio__handle(is_get);
            else if (slot <= CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE) 
                comm_service__endpoint__water_valve_controller__value__handle(is_get);
        }
    }
}
