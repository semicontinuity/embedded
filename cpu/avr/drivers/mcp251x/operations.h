#ifndef __CPU__AVR__DRIVERS__MCP251X__OPERATIONS_H
#define __CPU__AVR__DRIVERS__MCP251X__OPERATIONS_H

#include "device.h"

#include <stdint.h>


void mcp251x_reset (void);

void mcp251x_write_byte (const uint8_t address, const uint8_t data);
void mcp251x_write_bytes (uint8_t* buffer, const uint8_t address, uint8_t count);

uint8_t mcp251x_read_byte (const uint8_t address);
void mcp251x_read_bytes (uint8_t* buffer, const uint8_t address, uint8_t count);

/**
 * Issue Read RX Buffer command.
 * Note: associated RX flag bit in CANINTF will be clearead automatically once CS is set high.
 * @param instruction must be one of MCP251X_INSTRUCTION_READ_BUFFER_* commands
 */
void mcp2515_read_rx_buffer (uint8_t* buffer, const uint8_t instruction, uint8_t count);

void mcp2515_load_tx_buffer (const uint8_t* buffer, const uint8_t instruction, uint8_t count);


/**
 * Issue Read Status instruction
 */
uint8_t mcp2515_read_status (void);

/**
 * Issue Reuest To Send instruction
 */
void mcp2515_request_to_send (const uint8_t instruction);

#endif
