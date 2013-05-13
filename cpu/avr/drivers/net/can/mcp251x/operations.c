#include <stdint.h>
#include <avr/pgmspace.h>

#include "cpu/avr/asm.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/spi_polled.h"

#include "drivers/out/mcp251x_select.h"

// TODO: possible SPI failures not taken into account
// TODO: use interrupts for SPI

/**
 * Generic 1-byte instruction - used to implement reset, RTS, read status, RX status.
 * Saves FLASH space - only one function is used.
 * Calling code is a bit larger (instruction is specified)
 */
uint8_t mcp251x__command(const uint8_t instruction) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(instruction);
    const uint8_t r = spi__read();
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
    return r;
}


void mcp251x__write(const uint8_t address, const uint8_t data) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    spi__write(data);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
}


void mcp251x__write_bytes(const uint8_t* buffer, const uint8_t address, uint8_t count) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    spi__write_bytes(buffer, count);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
}


void mcp251x__write_bytes_progmem(const uint8_t address, uint8_t count, uint8_t * PROGMEM buffer) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_WRITE);
    spi__write(address);
    spi__write_bytes_P(buffer, count);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
}


uint8_t mcp251x__read(const uint8_t address) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_READ);
    spi__write(address);
    const uint8_t r = spi__read();
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
    return r;
}


void mcp251x__read_bytes(uint8_t* buffer, const uint8_t address, uint8_t count) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_READ);
    spi__write(address);
    spi__read_bytes(buffer, count);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
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
 * @return the updated pointer to the data buffer.
 */
uint8_t* mcp2515__read_rx_buffer(uint8_t* buffer, const uint8_t instruction, uint8_t count) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(instruction);
    uint8_t* end = spi__read_bytes(buffer, count);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
    return end;
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
void mcp2515__load_tx_buffer(const uint8_t* buffer, const uint8_t instruction, uint8_t count) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(instruction);
    spi__write_bytes(buffer, count);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
}


void mcp251x__bit_modify(const uint8_t address, const uint8_t mask, const uint8_t value) {
#ifdef MCP251X__USE_CS
    mcp251x_select__on();
#endif
    spi__write(MCP251X_INSTRUCTION_BIT_MODIFY);
    spi__write(address);
    spi__write(mask);
    spi__write(value);
#ifdef MCP251X__USE_CS
    mcp251x_select__off();
#endif
}
