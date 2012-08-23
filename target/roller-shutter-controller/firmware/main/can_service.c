#include <stdint.h>
#include <avr/interrupt.h>

#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/interrupt-codes.h"

#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


static volatile mcp251x_message_buffer buffer;


static void can_service__handle_rx(void) {
    uint8_t status;
    can_selector__run(status = mcp2515_rx_status());

    // For remote frames, read just the header.
    // For data frames, read the header + all 8 bytes of payload, even though DLC can be less than 8.
    uint8_t count = status & MCP251X__RX_STATUS__TYPE__REMOTE ? sizeof(buffer.header) : sizeof(buffer);
    uint8_t instruction = status & MCP251X__RX_STATUS__BUFFER__0 ? MCP251X_REGISTER_RXB0SIDH : MCP251X_REGISTER_RXB1SIDH;

    can_selector__run(mcp2515_read_rx_buffer((uint8_t*)&buffer.header, instruction, count));

    uint8_t slot = CANP_SLOT_BITS(buffer.header.id);

    // Assume that extended frame was received.
    // Check if it was an Remote Transmission Request: use RTR bit in DLC (extended frames only)
    if (status & MCP251X__RX_STATUS__TYPE__REMOTE) {
        // Received GET request
        // Leave only data length in dlc field, because the same buffer will be used for sending response without RTR set.
        // The message ID of the response is the same as for request, so it can be reused.

        buffer.header.dlc &= 0x0F;
    }
    else {
        // Received PUT request
    }
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
ISR(INT1_vect) {
    // interrupt flag for INT1 cleared automatically
    // The only source of interrupt is from RX buffer 0.
    // Clears interrupts.
    can_service__handle_rx();
}
