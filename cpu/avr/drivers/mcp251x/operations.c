#include "device.h"

#include <stdint.h>

#include "cpu/avr/drivers/mcp251x/operations.h"
#include "cpu/avr/drivers/mcp251x/instructions.h"
#include "cpu/avr/spi_polled.h"

// TODO: possible SPI failures not taken into account
// TODO: use interrupts for SPI

void mcp251x_reset()
{
    spi__exchange(MCP251X_INSTRUCTION_RESET);
}


void mcp251x_write_byte (const uint8_t address, const uint8_t data)
{
    spi__exchange(MCP251X_INSTRUCTION_WRITE);
    spi__exchange(address);
    spi__exchange(data);
}


void mcp251x_write_bytes (uint8_t* buffer, const uint8_t address, uint8_t count)
{
    spi__exchange(MCP251X_INSTRUCTION_WRITE);
    spi__exchange(address);
    do
    {
        spi__exchange(*buffer++);
    }
    while (--count > 0);
}


uint8_t mcp251x_read_byte (const uint8_t address)
{
    spi__exchange(MCP251X_INSTRUCTION_READ);
    spi__exchange(address);
    register uint8_t data = spi__exchange(0);

    return data;
}


void mcp251x_read_bytes (uint8_t* buffer, const uint8_t address, uint8_t count)
{
    spi__exchange(MCP251X_INSTRUCTION_READ);
    spi__exchange(address);
    do
    {
        *(buffer++) = spi__exchange(0);
    }
    while (--count > 0);
}


void mcp251x_bit_modify (const uint8_t address, const uint8_t mask, const uint8_t value)
{
    spi__exchange(MCP251X_INSTRUCTION_BIT_MODIFY);
    spi__exchange(address);
    spi__exchange(mask);
    spi__exchange(value);
}


void mcp2515_read_rx_buffer (uint8_t* buffer, const uint8_t instruction, uint8_t count)
{
    spi__exchange(instruction);
    do
    {
        *(buffer++) = spi__exchange(0);
    }
    while (--count > 0);
}


void mcp2515_load_tx_buffer (const uint8_t* buffer, const uint8_t instruction, uint8_t count)
{
    spi__exchange(instruction);
    do
    {
        spi__exchange(*buffer++);
    }
    while (--count > 0);
}


/**
 * Issue Request To Send instruction
 */
void mcp2515_request_to_send (const uint8_t instruction) {
    spi__exchange(instruction);
}


/**
 * Issue Read Status instruction
 */
uint8_t mcp2515_read_status () {
    spi__exchange(MCP251X_INSTRUCTION_READ_STATUS);
    return spi__exchange(0);
}
