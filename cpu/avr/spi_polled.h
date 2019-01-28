#ifndef __CPU_AVR_SPI_POLLED_H
#define __CPU_AVR_SPI_POLLED_H

#include <stdint.h>
#include <avr/pgmspace.h>


#if !defined(SPI_ATTRS)
#  define SPI_ATTRS
#endif

#if !defined(SPI_INLINE)
#  define SPI_INLINE
#endif

/**
 * SPI Exchange
 */
SPI_INLINE uint8_t spi__exchange(const uint8_t value) SPI_ATTRS;

/**
 * SPI write.
 * Same as SPI Exchange, but the received byte is ignored.
 * (If spi__exchange is used, the code is more verbose even though the result is not used)
 */
SPI_INLINE void spi__write(const uint8_t value) SPI_ATTRS;

/**
 * SPI read.
 * Same as SPI Exchange, but the sent byte is not specified.
 */
SPI_INLINE uint8_t spi__read(void) SPI_ATTRS;

// count > 0
SPI_INLINE void spi__write_bytes(const uint8_t* buffer, uint8_t count) SPI_ATTRS;

// count > 0 
SPI_INLINE const uint8_t * PROGMEM spi__write_bytes_P(const uint8_t * PROGMEM buffer, uint8_t count) SPI_ATTRS;


// count > 0
SPI_INLINE uint8_t* spi__read_bytes(uint8_t* buffer, uint8_t count) SPI_ATTRS;


#endif