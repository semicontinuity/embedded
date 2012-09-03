// =============================================================================
// Main program.
// =============================================================================

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"

#include "cpu/avr/spi.h"
#include "can_selector.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "motor.h"

// =============================================================================
// Entry point
// =============================================================================
int main(void) {
    motor__init();
    motor__up__on();

    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();

    usart__out__write(0xAA);
    usart__out__write(0x55);

    spi__init(SPI_CLKDIV_128);
    can_selector__init();
    mcp251x__init();

    motor__down__on();

    uint8_t b;

    while (1) {
        uint8_t a = usart0__in__read();
        can_selector__run(b = mcp251x_read_byte(a));
        usart__out__write(b);
    }
    return 0;
}
