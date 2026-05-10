// =============================================================================
// Main program.
// =============================================================================

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"

#include "cpu/avr/spi.h"
#include "drivers/out/mcp251x_select.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "motor.h"

// =============================================================================
// Entry point
// =============================================================================
int main(void) {
    motor__init();
    motor__up__on();

    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);

    usart0__putc(0xAA);
    usart0__putc(0x55);

    spi__init(SPI_CLKDIV_128);
    mcp251x_select__init();
    mcp251x__init();

    motor__down__on();

    uint8_t b;

    while (1) {
        const uint8_t a = usart0__getc();
        mcp251x_select__run(b = mcp251x__read(a));
        usart0__putc(b);
    }
    return 0;
}
