#ifndef __DRIVERS__NET__CAN__MCP251X__RX_H
#define __DRIVERS__NET__CAN__MCP251X__RX_H

#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


/**
 * Performs configuration of MCP251x message reception module.
 * Uploads all the data that remains constant during the operation of the device
 * - Masks
 * - Filters
 */ 
INLINE void mcp251x__rx__init(void);


/**
 * Reads the received CAN frame into the specified buffer.
 * @return the ID of the filter matched (one of MCP251X__RX_STATUS__FILTER__x constants)
 */
inline static uint8_t mcp2515__rx__read_frame(uint8_t *buffer) {
    uint8_t status = mcp2515__rx_status();

    // For remote frames, read just the header.
    // For data frames, read the header + all 8 bytes of payload, even though DLC can be less than 8.
    // (Optimize: start reading RX buffer, read header, check DLC and read DLC bytes additionally - all as one RX Buffer read.

    uint8_t count = status & MCP251X__RX_STATUS__TYPE__REMOTE ? sizeof(struct mcp251x_frame_header) : sizeof(struct mcp251x_message_buffer);

    uint8_t instruction = status & MCP251X__RX_STATUS__BUFFER__0 ? MCP251X_INSTRUCTION_READ_BUFFER_0_SIDH : MCP251X_INSTRUCTION_READ_BUFFER_1_SIDH;
    mcp2515__read_rx_buffer(buffer, instruction, count);

    return status & MCP251X__RX_STATUS__FILTER__MASK;
}


#endif

