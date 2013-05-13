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

#include "drivers/out/mcp251x_select.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
static inline void can_service__rx__run(void) {
    uint8_t status;
    debug__putc('>');

    mcp251x_select__run(status = mcp2515__read_status());

    if (status & (MCP251X__STATUS__RX0IF | MCP251X__STATUS__RX1IF)) {
        // Interrupt flag cleared automatically when proper RX buffer is read.
        kernel__rx__handle(can__read_frame((uint8_t*)&kernel__frame));
    }
    else {
        uint8_t mask;
        if (status & (MCP251X__STATUS__TX1IF)) {
            mask = 1 << MCP251X_TX1IF;
        }
        else {
            // MCP251X__STATUS__TX2IF
            mask = 1 << MCP251X_TX2IF;
        }
        // clear corresponding interrupt
        mcp251x_select__run(mcp251x__bit_modify(MCP251X_REGISTER_CANINTF, mask, 0));
        kernel__tx__handle(mask);
    }
    debug__putc('<');
}
