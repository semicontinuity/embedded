// =============================================================================
// Test 8-digit display
// =============================================================================

#include "display_dynamic8_spi.h"
#include "cpu/avr/spi.h"
#include "cpu/avr/spi_polled.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {

    spi__init(SPI_CLKDIV_16);
    display__init();
    display__on();

    for(;;) {
        spi__write(0xFF - 0x80);
        spi__write(0x01);
        _delay_ms(1);

        spi__write(0xFF - 0x40);
        spi__write(0x02);
        _delay_ms(1);

        spi__write(0xFF - 0x20);
        spi__write(0x04);
        _delay_ms(1);

        spi__write(0xFF - 0x10);
        spi__write(0x08);
        _delay_ms(1);

        spi__write(0xFF - 0x08);
        spi__write(0x10);
        _delay_ms(1);

        spi__write(0xFF - 0x04);
        spi__write(0x20);
        _delay_ms(1);

        spi__write(0xFF - 0x02);
        spi__write(0x40);
        _delay_ms(1);

        spi__write(0xFF - 0x01);
        spi__write(0x80);
        _delay_ms(1);
    }

    return 0;
}
