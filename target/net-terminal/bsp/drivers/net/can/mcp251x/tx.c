// =============================================================================
// MCP251X CAN Controller driver - message transmission.
//
// The following symbols must be defined in mcp251x__tx__conf.h:
//
// TXB1H, TXB2H
// =============================================================================

#include "drivers/net/can/mcp251x/tx.h"
#include "mcp251x__tx__conf.h"

// TX Buffer 1 Header
mcp251x_frame_header can__txb1_h PROGMEM = TXB1H;

// TX Buffer 2 Header
mcp251x_frame_header can__txb2_h PROGMEM = TXB2H;


/**
 * Performs configuration of MCP251x message transmission module.
 * Uploads all the data that remains constant during the operation of the device
 * - TX Buffer 1 header
 * - TX Buffer 2 header
 */ 
INLINE void mcp251x__tx__init(void) {
    // Note: could implement mcp2515__load_tx_buffer_progmem
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_TXB1SIDH, sizeof(can__txb1_h), (uint8_t* PROGMEM)&can__txb1_h);
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_TXB2SIDH, sizeof(can__txb2_h), (uint8_t* PROGMEM)&can__txb2_h);
}
