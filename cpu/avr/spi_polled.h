#ifndef __CPU_AVR_SPI_POLLED_H
#define __CPU_AVR_SPI_POLLED_H

#include <avr/io.h>
#include <stdint.h>

#include "cpu/avr/asm.h"

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)


/**
 * SPI Exchange
 */
inline uint8_t spi__exchange(uint8_t value) {
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

/**
 * SPI write.
 * Same as SPI Exchange, but the received byte is ignored.
 * (If spi__exchange is used, the code is more verbose even though the result is not used)
 */
inline void spi__write(uint8_t value) {
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
}

/**
 * SPI read.
 * Same as SPI Exchange, but the sent byte is not specified.
 */
inline uint8_t spi__read(void) {
    return spi__exchange(0);
}


// count > 0
inline void spi__write_bytes(const uint8_t* buffer, uint8_t count) {
    while (1) {
        uint8_t temp;
        LD_ZPLUS(temp, buffer);
        spi__write(temp);
        if (--count == 0) break;
    }
}

// count > 0 
inline static const uint8_t * PROGMEM spi__write_bytes_P(const uint8_t * PROGMEM buffer, uint8_t count) {
    do {
        spi__write(__LPM_increment__(buffer));
    }
    while (--count > 0);
    return buffer;
}


// count > 0
inline static uint8_t* spi__read_bytes(uint8_t* buffer, uint8_t count) {
    do {
        // optimize
        *(buffer++) = spi__read();
    }
    while (--count > 0);
    return buffer;
}



#else
#   error "Unsupported MCU"
#endif


#endif