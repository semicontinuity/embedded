#include <stdint.h>
#include "services/retained_registers.h"
#include "cpu/avr/eeprom.h"


/* MSB first */
void retained_registers__set(uint8_t address, uint16_t value) {
    uint16_t ee_address = address << 1;
    eeprom__write_byte((unsigned char *) ee_address, value >> 8);
    eeprom__write_byte((unsigned char *) (ee_address + 1), value & 0xFF);
}

/* MSB first */
uint16_t retained_registers__get(uint8_t address) {
    uint16_t ee_address = address << 1;
    uint8_t hi = eeprom__read_byte_unchecked((unsigned char *) ee_address);
    uint8_t lo = eeprom__read_byte_unchecked((unsigned char *) (ee_address + 1));
    return (hi << 8) | lo;
}
