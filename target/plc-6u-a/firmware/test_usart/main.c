#include "usart_rx.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "cpu/avr/usart0.h"



//int main(void) __attribute__ ((noreturn));
int main(void)
{
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
/*
    usart_rx_thread__init();
    usart_rx_thread__enabled__set(1);

    sei();
    for(;;);
*/
    for(;;) {
        char c = usart0__getc();
        usart0__putc(c);
    }
}
