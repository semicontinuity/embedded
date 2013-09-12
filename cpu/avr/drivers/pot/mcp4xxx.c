// =============================================================================
// Driver for Microchip 4XXX series SPI digital potentiometers.
//
// Chip Selects must be handled by the calling side.
// =============================================================================

#include "cpu/avr/drivers/pot/mcp4xxx.h"


void mcp4xxx__volatile_wiper_0_u8__set(const uint8_t value) {
    mcp4xxx__write_u8(MCP4XXX_REGISTER_VOLATILE_WIPER_0, value);
}

uint8_t mcp4xxx__volatile_wiper_0_u8__get(void) {
    return mcp4xxx__read_u8(MCP4XXX_REGISTER_VOLATILE_WIPER_0);
}

void mcp4xxx__volatile_wiper_1_u8__set(const uint8_t value) {
    mcp4xxx__write_u8(MCP4XXX_REGISTER_VOLATILE_WIPER_1, value);
}

uint8_t mcp4xxx__volatile_wiper_1_u8__get(void) {
    return mcp4xxx__read_u8(MCP4XXX_REGISTER_VOLATILE_WIPER_1);
}
