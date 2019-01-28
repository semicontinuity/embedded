// =============================================================================
// CRC8 computation (1-wire polynom).
// Adapted from Maxim/Dallas App Note.
// =============================================================================

#ifndef UTIL_CRC8_OW_H
#define UTIL_CRC8_OW_H

#include <stdint.h>

uint8_t crc8_ow_update(uint8_t crc, uint8_t data);

uint8_t crc8_ow(uint8_t *data, uint8_t length, uint8_t crc);


#endif
