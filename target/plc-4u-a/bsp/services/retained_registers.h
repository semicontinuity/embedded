#ifndef RETAINED_REGISTERS_H
#define RETAINED_REGISTERS_H


/* MSB first */
void retained_registers__set(uint8_t address, uint16_t value);

/* MSB first */
uint16_t retained_registers__get(uint8_t address);


#endif
