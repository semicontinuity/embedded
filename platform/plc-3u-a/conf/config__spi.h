#include <avr/sfr_defs.h>
#include "cpu/avr/gpio.h"

// Initialize SPI unit
// SS Must be configured as output for proper SPI operation, even if it is not use to select the chip.
    
// - SPIE=0: Don't enable interrupts. TODO: use interrupts
// - SPE =1: Enable SPI.
// - DORD=0: MSB first.
// - MSTR=1: Master. TODO: check that SS is not an input
// - CPOL=0: SCK is low when idle 
// - CPHA=0: Sample on leading edge, setup on trailing edge
// - SPR0=0, SPR1=0, combined with SPI2X=0: Set clock rate fck/4
// ( SPR0=1, SPR1=1, combined with SPI2X=0: Set clock rate fck/128)

static inline void spi__init(void) {
    CONFIGURE_AS_OUTPUT(SS);
    DRIVE_HIGH(SS);
//    CONFIGURE_AS_OUTPUT(MOSI);
//    CONFIGURE_AS_OUTPUT(SCK);
    SPCR=_BV(SPE)|_BV(MSTR)|_BV(SPR0);
}
