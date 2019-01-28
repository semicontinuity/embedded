/* 
 *  this source code is based on Rex and Binstock which, in turn,
 *  acknowledges William James Hunt.
 */

#include "util/crc16_table2x16.h"


const uint16_t crc16__table[16] PROGMEM = {
  0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
  0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
};


uint16_t crc16_update(uint16_t crc, const uint8_t b) {    
    const uint16_t r1 = pgm_read_word(&crc16__table[crc & 0x0F]);
    crc = (crc >> 4) & 0x0FFF;
    crc = crc ^ r1 ^ pgm_read_word(&crc16__table[b & 0x0F]);

    const uint16_t r2 = pgm_read_word(&crc16__table[crc & 0x0F]);
    crc = (crc >> 4) & 0x0FFF;
    crc = crc ^ r2 ^ pgm_read_word(&crc16__table[(b >> 4) & 0x0F]);

    return crc;
}


uint16_t crc16(uint16_t crc, uint8_t *p, int n) {
    while (n-- > 0) {
        crc = crc16_update(crc, *p++);
    }
    return crc;
}
