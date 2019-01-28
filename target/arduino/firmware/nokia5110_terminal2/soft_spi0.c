#include "soft_spi0.h"
#include "cpu/avr/gpio.h"

void soft_spi0__init(void) {
    USE_AS_OUTPUT(SOFT_SPI0__MOSI);
    USE_AS_OUTPUT(SOFT_SPI0__SCK);
}


void soft_spi0__write(uint8_t value) {
    uint8_t i = 8;
    do {
        OUT_0(SOFT_SPI0__SCK);
        if (value & 0x80) OUT_1(SOFT_SPI0__MOSI); else OUT_0(SOFT_SPI0__MOSI);
        value <<= 1;
        OUT_1(SOFT_SPI0__SCK);
    }
    while (--i);
}
