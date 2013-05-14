// =============================================================================
// CAN Controller driver.
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include <stdint.h>
#include <stdbool.h>

#include "drivers/out/mcp251x_select.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "cpu/avr/spi_polled.h"
#include "cpu/avr/usart0.h"

#include "util/bitops.h"

#include <util/delay.h>



#if defined(can__txb0__available__HOST) && defined(can__txb0__available__BIT)
DECLARE_BITVAR(can__txb0__available, can__txb0__available__HOST, can__txb0__available__BIT);
#else
inline void can__txb0__available__set(uint8_t value) {}
inline bool can__txb0__available__is_set(void) { return true; }
#endif

#if defined(can__txb1__available__HOST) && defined(can__txb1__available__BIT)
DECLARE_BITVAR(can__txb1__available, can__txb1__available__HOST, can__txb1__available__BIT);
#else
inline void can__txb1__available__set(uint8_t value) {}
inline bool can__txb1__available__is_set(void) { return true; }
#endif

#if defined(can__txb2__available__HOST) && defined(can__txb2__available__BIT)
DECLARE_BITVAR(can__txb2__available, can__txb2__available__HOST, can__txb2__available__BIT);
#else
inline void can__txb2__available__set(uint8_t value) {}
inline bool can__txb2__available__is_set(void) { return true; }
#endif



inline static void can__start(void) {
    can__txb0__available__set(1);
    can__txb1__available__set(1);
    can__txb2__available__set(1);
    mcp251x__write(MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL);
}


/**
 * Reads the received CAN frame into the specified buffer.
 * @return the ID of the filter matched (one of MCP251X__RX_STATUS__FILTER__x constants)
 */
inline static uint8_t can__read_frame(uint8_t *buffer) {
    uint8_t status = mcp2515__rx_status();

    // For remote frames, read just the header.
    // For data frames, read the header + all 8 bytes of payload, even though DLC can be less than 8.
    // (Optimize: start reading RX buffer, read header, check DLC and read DLC bytes additionally - all as one RX Buffer read.

    uint8_t count = status & MCP251X__RX_STATUS__TYPE__REMOTE ? sizeof(struct mcp251x_frame_header) : sizeof(struct mcp251x_message_buffer);

    uint8_t instruction = status & MCP251X__RX_STATUS__BUFFER__0 ? MCP251X_INSTRUCTION_READ_BUFFER_0_SIDH : MCP251X_INSTRUCTION_READ_BUFFER_1_SIDH;
    mcp2515__read_rx_buffer(buffer, instruction, count);

    return status & MCP251X__RX_STATUS__FILTER__MASK;
}

// Generic TX functions
// -----------------------------------------------------------------------------

inline static void can__load_txb_data(const uint8_t* buffer, uint8_t count, uint8_t instruction) {
    mcp2515__load_tx_buffer(buffer, instruction, count);
}

inline static void can__load_txb_report(const uint8_t report_id, const uint8_t count, const uint8_t* data, const uint8_t address) {
    mcp2515__load_tx_buffer__eid0_data(data, count, address, report_id);
}

inline static void can__load_txb_response(
    const uint8_t address,
    const uint8_t data_length,
    const uint8_t* id,
    const uint8_t* data) {
    mcp2515__load_txb_buffer__id_data(data, data_length, address, id);
}

inline static void can__load_txb_request(const uint8_t address, const uint8_t report_id) {
    mcp2515__load_txb_buffer__eid0_rtr(address, report_id);
}

inline static void can__request_to_send(const uint8_t instruction) {
    mcp2515__request_to_send(instruction);
}


// TXB0 functions
// -----------------------------------------------------------------------------

inline static void can__txb0__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, count);
}

inline static void can__txb0__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB0EID0);
}

inline static void can__txb0__load_response(const uint8_t dlc, const uint8_t* id, const uint8_t* data) {
    can__load_txb_response(MCP251X_REGISTER_TXB0SIDH, dlc, id, data);
}

inline static void can__txb0__load_request(const uint8_t report_id) {
    can__load_txb_request(MCP251X_REGISTER_TXB0EID0, report_id);
}

inline static void can__txb0__request_to_send(void) {
    can__txb0__available__set(0);
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0);
}


// TXB1 functions
// -----------------------------------------------------------------------------

inline static void can__txb1__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_1_SIDH, count);
}

inline static void can__txb1__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB1EID0);
}

inline static void can__txb1__load_request(const uint8_t report_id) {
    can__load_txb_request(MCP251X_REGISTER_TXB1EID0, report_id);
}

inline static void can__txb1__request_to_send(void) {
    can__txb1__available__set(0);
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1);
}

// TXB2 functions
// -----------------------------------------------------------------------------

inline static void can__txb2__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_2_SIDH, count);
}

inline static void can__txb2__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB2EID0);
}

inline static void can__txb2__load_request(const uint8_t report_id) {
    can__load_txb_request(MCP251X_REGISTER_TXB2EID0, report_id);
}

inline static void can__txb2__request_to_send(void) {
    can__txb2__available__set(0);
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2);
}


#endif