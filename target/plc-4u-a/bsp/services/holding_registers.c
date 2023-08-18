#include <stdint.h>
#include "services/holding_registers.h"
#include "services/retained_registers.h"


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
    if (address >= HOLDING_REGISTER__ADDRESS__MODBUS__DEVICE_ADDRESS) {
        retained_registers__set(address, value);
    }
    holding_registers__buffer__set(address, value);
}


void holding_registers__init(void) {
    holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__REBOOT, 0);
    holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__UPTIME__HOURS, 0);
    holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__UPTIME__SECONDS, 0);

    // retain RTC registers

    for (uint8_t a = HOLDING_REGISTER__ADDRESS__MODBUS__DEVICE_ADDRESS; a < MODBUS_SERVER__HOLDING_REGISTERS_COUNT; a++) {
        holding_registers__buffer__set(a, retained_registers__get(a));
    }
}
