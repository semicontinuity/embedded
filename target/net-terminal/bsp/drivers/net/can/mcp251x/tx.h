#ifndef __DRIVERS__NET__CAN__MCP251X__TX_H
#define __DRIVERS__NET__CAN__MCP251X__TX_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "util/bitops.h"


// TX Buffer 1 Header
extern const mcp251x_frame_header mcp2515__tx__txb1_h PROGMEM;

// TX Buffer 2 Header
extern const mcp251x_frame_header mcp2515__tx__txb2_h PROGMEM;


#if defined(mcp2515__tx__txb0__available__HOST) && defined(mcp2515__tx__txb0__available__BIT)
DECLARE_BITVAR(mcp2515__tx__txb0__available, mcp2515__tx__txb0__available__HOST, mcp2515__tx__txb0__available__BIT);
#else
inline void mcp2515__tx__txb0__available__set(uint8_t value) {}
inline bool mcp2515__tx__txb0__available__is_set(void) { return true; }
#endif

#if defined(mcp2515__tx__txb1__available__HOST) && defined(mcp2515__tx__txb1__available__BIT)
DECLARE_BITVAR(mcp2515__tx__txb1__available, mcp2515__tx__txb1__available__HOST, mcp2515__tx__txb1__available__BIT);
#else
inline void mcp2515__tx__txb1__available__set(uint8_t value) {}
inline bool mcp2515__tx__txb1__available__is_set(void) { return true; }
#endif

#if defined(mcp2515__tx__txb2__available__HOST) && defined(mcp2515__tx__txb2__available__BIT)
DECLARE_BITVAR(mcp2515__tx__txb2__available, mcp2515__tx__txb2__available__HOST, mcp2515__tx__txb2__available__BIT);
#else
inline void mcp2515__tx__txb2__available__set(uint8_t value) {}
inline bool mcp2515__tx__txb2__available__is_set(void) { return true; }
#endif


/**
 * Performs configuration of MCP251x message transmission module.
 * Uploads all the data that remains constant during the operation of the device
 * - TX Buffer 1 header
 * - TX Buffer 2 header
 */ 
INLINE void mcp251x__tx__init(void);


INLINE void mcp251x__tx__start(void);


// Generic TX functions
// -----------------------------------------------------------------------------

INLINE void mcp2515__tx__load_buffer(const uint8_t* buffer, uint8_t count, uint8_t instruction);
INLINE void mcp2515__tx__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* data, const uint8_t address);
INLINE void mcp2515__tx__load_response(const uint8_t address, const uint8_t data_length, const uint8_t* id, const uint8_t* data);
INLINE void mcp2515__tx__load_request(const uint8_t address, const uint8_t report_id);
INLINE void mcp2515__tx__request_to_send(const uint8_t instruction);


// TXB0 functions
// -----------------------------------------------------------------------------

inline static void mcp2515__tx__txb0__load_buffer(const uint8_t* buffer, uint8_t count) {
    mcp2515__tx__load_buffer(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, count);
}

inline static void mcp2515__tx__txb0__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    mcp2515__tx__load_report(report_id, count, buffer, MCP251X_REGISTER_TXB0EID0);
}

inline static void mcp2515__tx__txb0__load_response(const uint8_t dlc, const uint8_t* id, const uint8_t* data) {
    mcp2515__tx__load_response(MCP251X_REGISTER_TXB0SIDH, dlc, id, data);
}

inline static void mcp2515__tx__txb0__load_request(const uint8_t report_id) {
    mcp2515__tx__load_request(MCP251X_REGISTER_TXB0EID0, report_id);
}

inline static void mcp2515__tx__txb0__request_to_send(void) {
    mcp2515__tx__txb0__available__set(0);
    mcp2515__tx__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0);
}


// TXB1 functions
// -----------------------------------------------------------------------------

inline static void mcp2515__tx__txb1__load_buffer(const uint8_t* buffer, uint8_t count) {
    mcp2515__tx__load_buffer(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_1_SIDH, count);
}

inline static void mcp2515__tx__txb1__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    mcp2515__tx__load_report(report_id, count, buffer, MCP251X_REGISTER_TXB1EID0);
}

inline static void mcp2515__tx__txb1__load_request(const uint8_t report_id) {
    mcp2515__tx__load_request(MCP251X_REGISTER_TXB1EID0, report_id);
}

inline static void mcp2515__tx__txb1__request_to_send(void) {
    mcp2515__tx__txb1__available__set(0);
    mcp2515__tx__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1);
}

// TXB2 functions
// -----------------------------------------------------------------------------

inline static void mcp2515__tx__txb2__load_buffer(const uint8_t* buffer, uint8_t count) {
    mcp2515__tx__load_buffer(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_2_SIDH, count);
}

inline static void mcp2515__tx__txb2__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    mcp2515__tx__load_report(report_id, count, buffer, MCP251X_REGISTER_TXB2EID0);
}

inline static void mcp2515__tx__txb2__load_request(const uint8_t report_id) {
    mcp2515__tx__load_request(MCP251X_REGISTER_TXB2EID0, report_id);
}

inline static void mcp2515__tx__txb2__request_to_send(void) {
    mcp2515__tx__txb2__available__set(0);
    mcp2515__tx__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2);
}


#endif

