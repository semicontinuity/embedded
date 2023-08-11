#include <stdint.h>
#include "services/holding_registers.h"


uint8_t holding_registers__buffer[MODBUS_SERVER__HOLDING_REGISTERS_COUNT * 2];

/* MSB first */
void holding_registers__buffer__set(uint8_t address, uint16_t value) {
    holding_registers__buffer[(2 * address)] = value >> 8;
    holding_registers__buffer[(2 * address) + 1] = value & 0xFF;
}

/* MSB first */
uint16_t holding_registers__buffer__get(uint8_t address) {
    return (holding_registers__buffer[(2 * address)] << 8) | holding_registers__buffer[(2 * address) + 1];
}


/* MSB first */
void holding_registers__set(uint8_t address, uint16_t value) {
    if (address == 0x00) holding_registers__buffer__set(0x00, value);
    if (address == 0x01) holding_registers__buffer__set(0x01, value);
}
