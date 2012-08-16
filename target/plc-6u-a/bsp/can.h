// =============================================================================
// CAN Networking initialization.
//
// Uploads the data that are set in the Configuration mode of MCP251X:
//
// - Masks
// - Filters
//
// When the data are uploaded, the controller is switched into Normal Mode.
//
// The following constants must be defined:
//
// - CANP_DEVICE_NET	network id
// - CANP_DEVICE_ADDR	address in the network
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


// RX Filters 0-2
extern mcp251x_message_id rxf0_2[3] PROGMEM;

// RX Filters 3-5
extern mcp251x_message_id rxf3_5[3] PROGMEM;

// RX Masks 0 and 1
extern mcp251x_message_id rxm0_1[2] PROGMEM;


inline static void can__init(void) {
    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf0_2, MCP251X_REGISTER_RXF0SIDH, sizeof(rxf0_2)));
    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf3_5, MCP251X_REGISTER_RXF3SIDH, sizeof(rxf3_5)));
    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxm0_1, MCP251X_REGISTER_RXM0SIDH, sizeof(rxm0_1)));
}


inline void can__start(void) {
    can_selector__run(mcp251x_write_byte (MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}

#endif