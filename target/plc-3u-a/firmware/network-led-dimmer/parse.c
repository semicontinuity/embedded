#include <avr/io.h>
#include <stdint.h>


uint8_t parseByte(const uint8_t* __restrict const str) {
    register uint8_t last_error;
    register uint8_t c1 = str[0];
    if ((c1 < '0') || (c1 > 'F') || ((c1 > '9') && (c1 < 'A'))) last_error=1;

    register uint8_t c2 = str[1];
    if ((c2 < '0') || (c2 > 'F') || ((c2 > '9') && (c2 < 'A'))) last_error=1;

    register uint8_t x1 = ((c1 < 'A') ? (c1 & 0x0F) : (c1 - ('A' - 0x0A)));
    register uint8_t x2 = ((c2 < 'A') ? (c2 & 0x0F) : (c2 - ('A' - 0x0A)));
    last_error = 0;
    return (x1 << 4) | x2;
}
