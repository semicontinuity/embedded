#ifndef HOLDING_REGISTERS_H
#define HOLDING_REGISTERS_H


extern uint8_t holding_registers__bytes[MODBUS_SERVER__HOLDING_REGISTERS_COUNT * 2];

/* MSB first */
void holding_registers__set(uint8_t address, uint16_t value);

/* MSB first */
uint16_t holding_registers__get(uint8_t address);


#endif
