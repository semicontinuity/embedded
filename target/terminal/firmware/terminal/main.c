#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include <avr/interrupt.h>


int main(void) {
    terminal_init();
    usart0__rate__set(USART_BAUD_RATE);
    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();
    usart0__in__complete_interrupt_enabled__set();

    sei();

    for (;;) {
        uint8_t c = usart0__in__read();
        terminal_displayChar(c);
    }

    return 0;
}
