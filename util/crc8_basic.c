#include <stdint.h>

uint8_t crc8(register uint8_t crc, register uint8_t n) {
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