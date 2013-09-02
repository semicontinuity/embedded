#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include <avr/interrupt.h>


int main(void) {
    terminal_init();
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
    usart0__rx__complete__interrupt__enabled__set(1);

    sei();

    for (;;) {
        uint8_t c = usart0__getc();
        terminal_displayChar(c);
    }

    return 0;
}
