#include "usart_rx.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0.h"



//int main(void) __attribute__ ((noreturn));
int main(void)
{
    usart0__rate__set(USART_BAUD_RATE);
    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();
/*
    usart_rx_thread__init();
    usart_rx_thread__enabled__set(1);

    sei();
    for(;;);
*/
    for(;;) {
        char c = usart0__in__read();
        usart0__out__write(c);
    }
}
