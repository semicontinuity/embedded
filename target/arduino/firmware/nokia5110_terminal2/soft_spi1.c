#include "soft_spi1.h"
#include "cpu/avr/gpio.h"

void soft_spi1__init(void) {
    USE_AS_OUTPUT(SOFT_SPI1__MOSI);
    USE_AS_OUTPUT(SOFT_SPI1__SCK);
}


void soft_spi1__write(uint8_t value) {
    uint8_t i = 8;
    do {
        OUT_0(SOFT_SPI1__SCK);
        if (value & 0x80) OUT_1(SOFT_SPI1__MOSI); else OUT_0(SOFT_SPI1__MOSI);
        value <<= 1;
        OUT_1(SOFT_SPI1__SCK);
    }
    while (--i);
}
