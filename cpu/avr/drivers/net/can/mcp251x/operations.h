#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__OPERATIONS_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__OPERATIONS_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "cpu/avr/spi_polled.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


// Operations available in both MCP2510 and MCP2515
// =============================================================================
#ifndef MCP251X_attrs
#define MCP251X_attrs
#endif


inline void mcp251x__reset(void);

void mcp251x__write(const uint8_t address, const uint8_t data) MCP251X_attrs;
void mcp251x__write_bytes(const uint8_t* buffer, const uint8_t address, uint8_t count) MCP251X_attrs;
void mcp251x__write_bytes_progmem(const uint8_t address, uint8_t count, uint8_t * PROGMEM buffer) MCP251X_attrs;

uint8_t mcp251x__read(const uint8_t address) MCP251X_attrs;
void mcp251x__read_bytes(uint8_t* buffer, const uint8_t address, uint8_t count) MCP251X_attrs;

/**
 * Issue Read Status instruction.
 */
inline uint8_t mcp251x__read_status(void);

/**
 * Issue Request To Send instruction.
 * @param instruction   The instruction that determines TX buffers for which to initiate transmission.
 *                      Must be a bitwise combination of MCP251X_INSTRUCTION_REQUEST_TO_SEND constant
 *                      and any number of the following constants:
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2
 */
inline void mcp251x__request_to_send(const uint8_t instruction);

/**
 * Issue Bit Modify instruction.
 * Set or clear individual bits.
 */
void mcp251x__bit_modify(const uint8_t address, const uint8_t mask, const uint8_t value) MCP251X_attrs;

#define mcp2515__reset                   mcp251x__reset
#define mcp2515__write                   mcp251x__write
#define mcp2515__write_bytes             mcp251x__write_bytes
#define mcp2515__write_bytes_progmem     mcp251x__write_bytes_progmem
#define mcp2515__read                    mcp251x__read
#define mcp2515__read_bytes              mcp251x__read_bytes
#define mcp2515__read_status             mcp251x__read_status
#define mcp2515__bit_modify              mcp251x__bit_modify
#define mcp2515__request_to_send         mcp251x__request_to_send


// Operations available only for MCP2515
// =============================================================================

/**
 * Issue Read RX Buffer instruction.
 * Note: associated RX flag bit in CANINTF will be clearead automatically once CS is set high.
 * @param instruction must be one of MCP251X_INSTRUCTION_READ_BUFFER_* commands
 */
uint8_t* mcp2515__read_rx_buffer(uint8_t* buffer, const uint8_t instruction, uint8_t count) MCP251X_attrs;


/**
 * Issue Load TX Buffer instruction.
 */
void mcp2515__load_tx_buffer(const uint8_t* buffer, const uint8_t instruction, uint8_t count) MCP251X_attrs;


/**
 * Issue RX Status instruction.
 * A command to quickly read RX Status byte.
 */
inline uint8_t mcp2515__rx_status(void);


// Implementation of generic 1-byte instructions
// =============================================================================
uint8_t mcp251x__command(const uint8_t instruction) MCP251X_attrs;

inline void mcp251x__reset(void) {
    mcp251x__command(MCP251X_INSTRUCTION_RESET);
}

inline void mcp2515__request_to_send(const uint8_t instruction) {
    mcp251x__command(instruction);
}

inline uint8_t mcp251x__read_status(void) {
    return mcp251x__command(MCP251X_INSTRUCTION_READ_STATUS);
}

inline uint8_t mcp2515__rx_status(void) {
    return mcp251x__command(MCP251X_INSTRUCTION_RX_STATUS);
}


#endif
