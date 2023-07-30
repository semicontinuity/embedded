#include <stdint.h>
#include "services/holding_registers.h"


uint8_t holding_registers__bytes[MODBUS_SERVER__HOLDING_REGISTERS_COUNT * 2];


/* MSB first */
void holding_registers__set(uint8_t address, uint16_t value) {
    holding_registers__bytes[(2 * address)] = value >> 8;
    holding_registers__bytes[(2 * address) + 1] = value & 0xFF;
}

/* MSB first */
uint16_t holding_registers__get(uint8_t address) {
    return (holding_registers__bytes[(2 * address)] << 8) | holding_registers__bytes[(2 * address) + 1];
}
