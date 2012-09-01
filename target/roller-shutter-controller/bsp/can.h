// =============================================================================
// CAN Controller driver.
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include <stdint.h>

#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "cpu/avr/spi_polled.h"


// RX Filters 0-2 (uploaded as one piece)
extern mcp251x_message_id can__rxf0_2[3] PROGMEM;

// RX Filters 3-5 (uploaded as one piece)
extern mcp251x_message_id can__rxf3_5[3] PROGMEM;

// RX Masks 0 and 1 (uploaded as one piece)
extern mcp251x_message_id can__rxm0_1[2] PROGMEM;

// TX Buffer 1 Header
extern mcp251x_frame_header can__txb1_h PROGMEM;

// TX Buffer 2 Header
extern mcp251x_frame_header can__txb2_h PROGMEM;


/**
 * Performs MCP251x controller configuration.
 * Uploads all the data that remains constant during the operation of the device
 * - Masks
 * - Filters
 * - TX Buffer 1 header
 * - TX Buffer 2 header
 */ 
inline static void can__init(void) {
    can_selector__run(mcp2515_write_bytes_progmem(MCP251X_REGISTER_RXF0SIDH, sizeof(can__rxf0_2), (uint8_t* PROGMEM)&can__rxf0_2));
    can_selector__run(mcp2515_write_bytes_progmem(MCP251X_REGISTER_RXF3SIDH, sizeof(can__rxf3_5), (uint8_t* PROGMEM)&can__rxf3_5));
    can_selector__run(mcp2515_write_bytes_progmem(MCP251X_REGISTER_RXM0SIDH, sizeof(can__rxm0_1), (uint8_t* PROGMEM)&can__rxm0_1));

    // Note: could implement mcp2515_load_tx_buffer_progmem
    can_selector__run(mcp2515_write_bytes_progmem(MCP251X_REGISTER_TXB1SIDH, sizeof(can__txb1_h), (uint8_t* PROGMEM)&can__txb1_h));
    can_selector__run(mcp2515_write_bytes_progmem(MCP251X_REGISTER_TXB2SIDH, sizeof(can__txb2_h), (uint8_t* PROGMEM)&can__txb2_h));
}


inline static void can__start(void) {
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}


inline static uint8_t can__read_frame(uint8_t *buffer) {
    uint8_t status;
    can_selector__run(status = mcp2515_rx_status());

    // For remote frames, read just the header.
    // For data frames, read the header + all 8 bytes of payload, even though DLC can be less than 8.
    uint8_t count = status & MCP251X__RX_STATUS__TYPE__REMOTE ? sizeof(struct mcp251x_message_id) : sizeof(struct mcp251x_frame_header);
    uint8_t instruction = status & MCP251X__RX_STATUS__BUFFER__0 ? MCP251X_REGISTER_RXB0SIDH : MCP251X_REGISTER_RXB1SIDH;

    can_selector__run(mcp2515_read_rx_buffer(buffer, instruction, count));

    return status & MCP251X__RX_STATUS__FILTER__MASK;
}

// Generic TX functions
// -----------------------------------------------------------------------------

inline static void can__load_txb_data(const uint8_t* buffer, uint8_t count, uint8_t instruction) {
    can_selector__run(mcp2515_load_tx_buffer(buffer, instruction, count));
}

inline static void can__load_txb_report(const uint8_t report_id, const uint8_t count, const uint8_t* data, const uint8_t address) {
    can_selector__on();
    mcp2515_write(address);
    spi__write(report_id);              // to EID0 register
    spi__write(count);                  // to DLC register
    spi__write_bytes(data, count);      // to D0 register and on (payload)
    can_selector__off();
}

inline static void can__load_txb_response(
    const uint8_t address,
    const uint8_t sidh,
    const uint8_t sidl,
    const uint8_t eid8,
    const uint8_t eid0,
    const uint8_t dlc,
    const uint8_t* data) {

    can_selector__on();
    mcp2515_write(address);
    spi__write(sidh);
    spi__write(sidl);
    spi__write(eid8);
    spi__write(eid0);
    spi__write(dlc);
    spi__write_bytes(data, dlc);
    can_selector__off();
}

inline static void can__load_txb_response_(
    const uint8_t address,
    const uint8_t dlc,
    const uint8_t* id,
    const uint8_t* data) {

    can_selector__on();
    mcp2515_write(address);
    spi__write_bytes(id, 4);
    spi__write(dlc);
    spi__write_bytes(data, dlc);
    can_selector__off();
}

inline static void can__request_to_send(const uint8_t instruction) {
    can_selector__run(mcp2515_request_to_send(instruction));
}


// TXB0 functions
// -----------------------------------------------------------------------------

inline static void can__txb0__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, count);
}

inline static void can__txb0__load_data(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_D0, count);
}

inline static void can__txb0__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB0EID0);
}

inline static void can__txb0__load_response(const uint8_t sidh, const uint8_t sidl, const uint8_t eid8, const uint8_t eid0, const uint8_t dlc, const uint8_t* data) {
    can__load_txb_response(MCP251X_REGISTER_TXB0SIDH, sidh, sidl, eid8, eid0, dlc, data);
}

inline static void can__txb0__load_response_(const uint8_t dlc, const uint8_t* id, const uint8_t* data) {
    can__load_txb_response_(MCP251X_REGISTER_TXB0SIDH, dlc, id, data);
}

inline static void can__txb0__request_to_send(void) {
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0);
}


// TXB1 functions
// -----------------------------------------------------------------------------

inline static void can__txb1__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_1_SIDH, count);
}

inline static void can__txb1__load_data(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_1_D0, count);
}

inline static void can__txb1__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB1EID0);
}

inline static void can__txb1__request_to_send(void) {
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1);
}

// TXB2 functions
// -----------------------------------------------------------------------------

inline static void can__txb2__load_buffer(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_2_SIDH, count);
}

inline static void can__txb2__load_data(const uint8_t* buffer, uint8_t count) {
    can__load_txb_data(buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_2_D0, count);
}

inline static void can__txb2__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* buffer) {
    can__load_txb_report(report_id, count, buffer, MCP251X_REGISTER_TXB2EID0);
}

inline static void can__txb2__request_to_send(void) {
    can__request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2);
}


#endif