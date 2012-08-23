#ifndef __CPU_AVR_SPI_POLLED_H
#define __CPU_AVR_SPI_POLLED_H

#include <avr/io.h>
#include <stdint.h>

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)

/**
 * SPI Exchange (polled)
 */
inline uint8_t spi__exchange(uint8_t value) {
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

/**
 * SPI write (polled).
 * Same as SPI Exchange, but the received byte is ignored.
 */
inline void spi__write(uint8_t value) {
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
}


inline void spi__write_bytes(const uint8_t* buffer, uint8_t count) {
    do {
        spi__write(*buffer++);
    }
    while (--count > 0);
}

#else
#   error "Unsupported MCU"
#endif


#endif