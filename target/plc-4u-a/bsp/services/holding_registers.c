#include <stdint.h>
#include "services/holding_registers.h"


uint8_t holding_registers__buffer[MODBUS_SERVER__HOLDING_REGISTERS_COUNT * 2];



void holding_registers__buffer__set_u8_hi(uint8_t address, uint8_t value) {
    holding_registers__buffer[(2 * address)] = value;
}

void holding_registers__buffer__set_u8_lo(uint8_t address, uint8_t value) {
    holding_registers__buffer[(2 * address) + 1] = value;
}

/* MSB first */
uint8_t holding_registers__buffer__get_u8_hi(uint8_t address) {
    return holding_registers__buffer[(2 * address)];
}

/* MSB first */
uint8_t holding_registers__buffer__get_u8_lo(uint8_t address) {
    return holding_registers__buffer[(2 * address) + 1];
}


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
    if (address == 0x02) holding_registers__buffer__set(0x02, value);
    if (address == 0x03) holding_registers__buffer__set(0x03, value);
}


void holding_registers__init(void) {
    holding_registers__buffer__set(0, 0);
    holding_registers__buffer__set(1, 0);
    // retain RTC registers
}
