#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__OPERATIONS_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__OPERATIONS_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "cpu/avr/spi_polled.h"


// Operations available in both MCP2510 and MCP2515
// =============================================================================
#ifndef MCP251X_attrs
#define MCP251X_attrs
#endif


void mcp251x_reset (void) MCP251X_attrs;

void mcp251x_write (const uint8_t address) MCP251X_attrs;
void mcp251x_write_one_byte (const uint8_t address, const uint8_t data) MCP251X_attrs;
void mcp251x_write_bytes (const uint8_t* buffer, const uint8_t address, uint8_t count) MCP251X_attrs;
void mcp251x_write_bytes_progmem(const uint8_t address, uint8_t count, uint8_t * PROGMEM buffer) MCP251X_attrs;

uint8_t mcp251x_read_byte (const uint8_t address) MCP251X_attrs;
void mcp251x_read_bytes (uint8_t* buffer, const uint8_t address, uint8_t count) MCP251X_attrs;


// Operations available only in MCP2515
// =============================================================================

#define mcp2515_reset                   mcp251x_reset
#define mcp2515_write                   mcp251x_write
#define mcp2515_write_one_byte          mcp251x_write_one_byte
#define mcp2515_write_bytes             mcp251x_write_bytes
#define mcp2515_write_bytes_progmem     mcp251x_write_bytes_progmem
#define mcp2515_write_bytes_progmem1    mcp251x_write_bytes_progmem1
#define mcp2515_read_byte               mcp251x_read_byte
#define mcp2515_read_bytes              mcp251x_read_bytes

/**
 * Issue Read RX Buffer instruction.
 * Note: associated RX flag bit in CANINTF will be clearead automatically once CS is set high.
 * @param instruction must be one of MCP251X_INSTRUCTION_READ_BUFFER_* commands
 */
uint8_t* mcp2515_read_rx_buffer (uint8_t* buffer, const uint8_t instruction, uint8_t count) MCP251X_attrs;


/**
 * Issue Load TX Buffer instruction.
 */
void mcp2515_load_tx_buffer (const uint8_t* buffer, const uint8_t instruction, uint8_t count) MCP251X_attrs;


/**
 * Issue Read Status instruction.
 */
uint8_t mcp2515_read_status (void) MCP251X_attrs;


/**
 * Issue RX Status instruction.
 * A command to quickly read RX Status byte.
 */
uint8_t mcp2515_rx_status (void) MCP251X_attrs;

/**
 * Issue Request To Send instruction.
 */
void mcp2515_request_to_send (const uint8_t instruction) MCP251X_attrs;

void mcp251x_bit_modify(const uint8_t address, const uint8_t mask, const uint8_t value) MCP251X_attrs;

#endif
