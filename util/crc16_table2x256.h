#ifndef CRC16_TABLE_2x256_H
#define CRC16_TABLE_2x256_H

#include <stdint.h>

uint16_t crc16(uint16_t crc, uint8_t *data, uint16_t length);

#endif
