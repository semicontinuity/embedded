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
    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();

    usart0__out__write(0xAA);
    usart0__out__write(0x55);

    spi__init(SPI_CLKDIV_128);
    mcp251x_select__init();
    mcp251x__init();

    motor__down__on();

    uint8_t b;

    while (1) {
        uint8_t a = usart0__in__read();
        mcp251x_select__run(b = mcp251x_read_byte(a));
        usart0__out__write(b);
    }
    return 0;
}
