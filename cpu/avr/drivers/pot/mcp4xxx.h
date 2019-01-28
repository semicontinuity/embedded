// =============================================================================
// Driver for Microchip 4XXX series SPI digital potentiometers.
//
// Chip Selects must be handled by the calling side.
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__POT__MCP4XXX_H
#define __CPU__AVR__DRIVERS__POT__MCP4XXX_H

#include <stdint.h>
#include "cpu/avr/spi_polled.h"


#define MCP4XXX_COMMAND_READ                (0x0A00)
#define MCP4XXX_COMMAND_WRITE               (0x0000)
#define MCP4XXX_COMMAND_INCREMENT           (0x0400)
#define MCP4XXX_COMMAND_DECREMENT           (0x0800)

#define MCP4XXX_REGISTER_VOLATILE_WIPER_0   (0x00)
#define MCP4XXX_REGISTER_VOLATILE_WIPER_1   (0x01)
#define MCP4XXX_REGISTER_VOLATILE_TCON      (0x04)
#define MCP4XXX_REGISTER_STATUS             (0x05)


inline void mcp4xxx__write_u8(const uint8_t r, const uint8_t data) {
    spi__write((uint8_t)((MCP4XXX_COMMAND_WRITE >> 8) | (r << 4)));
    spi__write(data);
}

inline uint8_t mcp4xxx__read_u8(const uint8_t r) {
    spi__write((uint8_t)((MCP4XXX_COMMAND_READ >> 8) | (r << 4)));
    return spi__read();
}


void mcp4xxx__volatile_wiper_0_u8__set(const uint8_t value);
uint8_t mcp4xxx__volatile_wiper_0_u8__get(void);
void mcp4xxx__volatile_wiper_1_u8__set(const uint8_t value);
uint8_t mcp4xxx__volatile_wiper_1_u8__get(void);


#endif
