#ifndef __CPU_AVR_SPI_H
#define __CPU_AVR_SPI_H

#include <avr/sfr_defs.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)


// SS signal of SPI interface. For SPI master, usually configured as output.
#define SS_PORT       (PORTB)
#define SS_DIR        (DDRB)
#define SS_PIN        (2)


// SS signal of SPI interface. For SPI master, usually configured as output.
#define SS__PORT      B
#define SS__PIN       2


#else
#   error "Unsupported MCU"
#endif




#endif