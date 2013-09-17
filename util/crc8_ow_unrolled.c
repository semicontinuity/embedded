// =============================================================================
// CRC8 computation (1-wire polynom).
// Adapted from Maxim/Dallas App Note.
// =============================================================================
#include "util/crc8_ow.h"


uint8_t crc8_ow_update(uint8_t crc, uint8_t n) {
    n ^= crc;
    crc = 0;
    if (n & 0x01) crc  = 0x5E;
    if (n & 0x02) crc ^= 0xBC;
    if (n & 0x04) crc ^= 0x61;
    if (n & 0x08) crc ^= 0xC2;
    if (n & 0x10) crc ^= 0x9D;
    if (n & 0x20) crc ^= 0x23;
    if (n & 0x40) crc ^= 0x46;
    if (n & 0x80) crc ^= 0x8C;
    return crc;
}


uint8_t crc8_ow(uint8_t *data, uint8_t length, uint8_t crc) {
    while (length--) {
        crc = crc8_ow_update(crc, *data++);
    }
    return crc;
}
