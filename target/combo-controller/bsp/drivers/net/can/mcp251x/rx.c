// =============================================================================
// MCP251X CAN Controller driver - message reception.
//
// The following symbols must be defined in mcp251x__rx__conf.h:
//
// RXF0, RXF1, RXF2, RXF3, RXF4, RXF5
// RXM0, RXM1
// =============================================================================

#include "drivers/net/can/mcp251x/rx.h"
#include "mcp251x__rx__conf.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include <avr/pgmspace.h>


// RX Filters 0-2 (uploaded as one piece)
mcp251x_message_id mcp2515__rx__rxf0_2[3] PROGMEM = {RXF0, RXF1, RXF2};

// RX Filters 3-5 (uploaded as one piece)
mcp251x_message_id mcp2515__rx__rxf3_5[3] PROGMEM = {RXF3, RXF4, RXF5};

// RX Masks 0 and 1 (uploaded as one piece)
mcp251x_message_id mcp2515__rx__rxm0_1[2] PROGMEM = {RXM0, RXM1};


/**
 * Performs configuration of MCP251x message reception module.
 * Uploads all the data that remains constant during the operation of the device
 * - Masks
 * - Filters
 */ 
INLINE void mcp251x__rx__init(void) {
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_RXF0SIDH, sizeof(mcp2515__rx__rxf0_2), (uint8_t* PROGMEM)&mcp2515__rx__rxf0_2);
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_RXF3SIDH, sizeof(mcp2515__rx__rxf3_5), (uint8_t* PROGMEM)&mcp2515__rx__rxf3_5);
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_RXM0SIDH, sizeof(mcp2515__rx__rxm0_1), (uint8_t* PROGMEM)&mcp2515__rx__rxm0_1);
}
