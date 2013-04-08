// =============================================================================
// CAN service.
// Handles CAN communications (services incoming requests).
// Extends comm_service.
//
// The device is designed for the system with one super-node ("master").
// The master is the only device that can send messages to the node.
//
// If the master has sent GET request to the node,
// it should not send other GET requests to the node until it receives response.
// If the responce is not received in certain time,
// the master assumes that the node is malfunctioning.
// =============================================================================
#include "can_service.h"

#include <util/delay.h>

/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
static inline void can_service__rx__run(void) {
    // Interrupt flag cleared automatically when proper RX buffer is read.
    kernel__rx__handle(can__read_frame((uint8_t*)&kernel__frame));
    // Clear all interrupts
    //can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTF, 0));
}


INLINE void int0__run(void) {
    can_service__rx__run();
}