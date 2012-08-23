#include <stdint.h>
#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/spi_polled.h"

// TODO: possible SPI failures not taken into account
// TODO: use interrupts for SPI

void mcp251x_reset() {
    spi__write(MCP251X_INSTRUCTION_RESET);
}


void mcp251x_write(const uint8_t address) {
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
}


void mcp251x_write_one_byte(const uint8_t address, const uint8_t data) {
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    spi__write(data);
}


void mcp251x_write_bytes(const uint8_t* buffer, const uint8_t address, uint8_t count) {
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    do {
        spi__write(*buffer++);
    }
    while (--count > 0);
}


void mcp251x_write_bytes_progmem(uint8_t * PROGMEM buffer, const uint8_t address, uint8_t count) {
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    do {
        spi__write(pgm_read_byte(buffer++));
    }
    while (--count > 0);
}


uint8_t mcp251x_read_byte(const uint8_t address) {
    spi__write(MCP251X_INSTRUCTION_READ);
    spi__write(address);
    register uint8_t data = spi__exchange(0);

    return data;
}


void mcp251x_read_bytes(uint8_t* buffer, const uint8_t address, uint8_t count) {
    spi__write(MCP251X_INSTRUCTION_READ);
    spi__write(address);
    do {
        *(buffer++) = spi__exchange(0);
    }
    while (--count > 0);
}


void mcp251x_bit_modify(const uint8_t address, const uint8_t mask, const uint8_t value) {
    spi__write(MCP251X_INSTRUCTION_BIT_MODIFY);
    spi__write(address);
    spi__write(mask);
    spi__write(value);
}


/**
 * Read data from the specified RX Buffer.
 * @param buffer        The pointer to the data buffer.
 * @param instruction   The instruction that determines the RX buffer to read and a position in it.
 *                      Must be one of the following constants:
 *                      * MCP251X_INSTRUCTION_READ_BUFFER_0_SIDH
 *                      * MCP251X_INSTRUCTION_READ_BUFFER_0_D0
 *                      * MCP251X_INSTRUCTION_READ_BUFFER_1_SIDH
 *                      * MCP251X_INSTRUCTION_READ_BUFFER_1_D0
 * @param count         The number of bytes to read.
 */
void mcp2515_read_rx_buffer(uint8_t* buffer, const uint8_t instruction, uint8_t count) {
    spi__write(instruction);
    do {
        *(buffer++) = spi__exchange(0);
    }
    while (--count > 0);
}


/**
 * Load data into the specified TX Buffer.
 * @param buffer        The pointer to the data to be loaded.
 * @param instruction   The instruction that determines TX buffer to load and a position in it.
 *                      Must be one of the following constants:
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_0_D0
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_1_SIDH
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_1_D0
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_2_SIDH
 *                      * MCP251X_INSTRUCTION_LOAD_BUFFER_2_D0
 * @param count         The number of bytes to load.
 */
void mcp2515_load_tx_buffer(const uint8_t* buffer, const uint8_t instruction, uint8_t count) {
    spi__write(instruction);
    do {
        spi__write(*buffer++);
    }
    while (--count > 0);
}


/**
 * Issue Request To Send instruction.
 * @param instruction   The instruction that determines TX buffers for which to initiate transmission.
 *                      Must be a bitwise combination of MCP251X_INSTRUCTION_REQUEST_TO_SEND constant
 *                      and any number of the  following constants:
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1
 *                      * MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2
 */
void mcp2515_request_to_send(const uint8_t instruction) {
    spi__write(instruction);
}


/**
 * Issue Read Status instruction.
 */
uint8_t mcp2515_read_status(void) {
    spi__write(MCP251X_INSTRUCTION_READ_STATUS);
    return spi__exchange(0);
}


/**
 * Issue RX Status instruction.
 * A command to quickly read RX Status byte.
 */
uint8_t mcp2515_rx_status(void) {
    spi__write(MCP251X_INSTRUCTION_RX_STATUS);
    return spi__exchange(0);
}

