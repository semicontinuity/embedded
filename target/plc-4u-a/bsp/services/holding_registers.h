#ifndef HOLDING_REGISTERS_H
#define HOLDING_REGISTERS_H


extern uint8_t holding_registers__buffer[MODBUS_SERVER__HOLDING_REGISTERS_COUNT * 2];

uint8_t holding_registers__buffer__get_u8_hi(uint8_t address);
uint8_t holding_registers__buffer__get_u8_lo(uint8_t address);
void holding_registers__buffer__set_u8_hi(uint8_t address, uint8_t value);
void holding_registers__buffer__set_u8_lo(uint8_t address, uint8_t value);


/* MSB first */
void holding_registers__buffer__set(uint8_t address, uint16_t value);

/* MSB first */
uint16_t holding_registers__buffer__get(uint8_t address);


/* MSB first */
void holding_registers__set(uint8_t address, uint16_t value);

/* MSB first */
uint16_t holding_registers__get(uint8_t address);


#endif
