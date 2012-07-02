#ifndef __CPU_AVR_SPI_POLLED_H
#define __CPU_AVR_SPI_POLLED_H

#include <avr/io.h>
#include <stdint.h>

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)

// polled
// TODO: in some use cases output or input value is ignored.
inline uint8_t spi__exchange(uint8_t value)
{
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

#else
#   error "Unsupported MCU"
#endif


#endif