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
mcp251x_frame_header mcp2515__tx__txb1_h PROGMEM = TXB1H;

// TX Buffer 2 Header
mcp251x_frame_header mcp2515__tx__txb2_h PROGMEM = TXB2H;


/**
 * Performs configuration of MCP251x message transmission module.
 * Uploads all the data that remains constant during the operation of the device
 * - TX Buffer 1 header
 * - TX Buffer 2 header
 */ 
INLINE void mcp251x__tx__init(void) {
    // Note: could implement mcp2515__load_tx_buffer_progmem
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_TXB1SIDH, sizeof(mcp2515__tx__txb1_h), (uint8_t* PROGMEM)&mcp2515__tx__txb1_h);
    mcp2515__write_bytes_progmem(MCP251X_REGISTER_TXB2SIDH, sizeof(mcp2515__tx__txb2_h), (uint8_t* PROGMEM)&mcp2515__tx__txb2_h);
}


INLINE void mcp251x__tx__start(void) {
    mcp2515__tx__txb0__available__set(1);
    mcp2515__tx__txb1__available__set(1);
    mcp2515__tx__txb2__available__set(1);
}

// Generic TX functions
// -----------------------------------------------------------------------------

INLINE void mcp2515__tx__load_buffer(const uint8_t* buffer, uint8_t count, uint8_t instruction) {
    mcp2515__load_tx_buffer(buffer, instruction, count);
}

INLINE void mcp2515__tx__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* data, const uint8_t address) {
    mcp2515__load_tx_buffer__eid0_data(data, count, address, report_id);
}

INLINE void mcp2515__tx__load_response(const uint8_t address, const uint8_t data_length, const uint8_t* id, const uint8_t* data) {
    mcp2515__load_txb_buffer__id_data(data, data_length, address, id);
}

INLINE void mcp2515__tx__load_request(const uint8_t address, const uint8_t report_id) {
    mcp2515__load_txb_buffer__eid0_rtr(address, report_id);
}

INLINE void mcp2515__tx__request_to_send(const uint8_t instruction) {
    mcp2515__request_to_send(instruction);
}
