#ifndef __CPU_AVR_SPI_H
#define __CPU_AVR_SPI_H

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>

#include "cpu/avr/gpio.h"


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega8__)


// SS signal of SPI interface. For SPI master, usually configured as output.
#define SS__PORT      B
#define SS__PIN       2

#define MOSI__PORT    B
#define MOSI__PIN     3

#define SCK__PORT     B
#define SCK__PIN      5

#elif defined(__AVR_ATmega16__)

// SS signal of SPI interface. For SPI master, usually configured as output.
#define SS__PORT      B
#define SS__PIN       4

#define MOSI__PORT    B
#define MOSI__PIN     5

#define SCK__PORT     B
#define SCK__PIN      7

#else
#   error "Unsupported MCU"
#endif


// There are the following 8 modes:
// (add 2x modes)
#define SPI_CLKDIV_4    (                    0)
#define SPI_CLKDIV_16   (            _BV(SPR0))
#define SPI_CLKDIV_64   (_BV(SPR1)            )
#define SPI_CLKDIV_128  (_BV(SPR1) | _BV(SPR0))


// Initialize SPI unit for master operation
// - SPIE=0: Don't enable interrupts. TODO: use interrupts
// - SPE =1: Enable SPI.
// - DORD=0: MSB first.
// - MSTR=1: Master. TODO: check that SS is not an input
// - CPOL=0: SCK is low when idle 
// - CPHA=0: Sample on leading edge, setup on trailing edge
static inline void spi__init(const uint8_t clock_divisor) {
    // MOSI MUST be configured as output for proper SPI MASTER operation - pin not configured as output automatically.
    USE_AS_OUTPUT(MOSI);

    // SCK MUST be configured as output for proper SPI MASTER operation - pin not configured as output automatically.
    USE_AS_OUTPUT(SCK);

    // SS MUST be configured as output for proper SPI MASTER operation, even if it is not use to select the chip.
    USE_AS_OUTPUT(SS);
    OUT_1(SS);

    // MOSI, SCK are automatically configured as outputs 
    SPCR=_BV(SPE)|_BV(MSTR)|clock_divisor;
}

static inline void spi__double_speed__set(const uint8_t is2x) {
    if (is2x)
        SPSR |=_BV(SPI2X);
    else
        SPSR &=~_BV(SPI2X);
}



#endif