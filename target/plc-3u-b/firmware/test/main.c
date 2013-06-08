#include <avr/io.h>
#include <avr/interrupt.h>
//#include "cpu/avr/spi.h"
#include "services/console.h"

#include <stdio.h>

int usart_putchar(char c, FILE *stream)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;
    return 0;
}

FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);


int main(void) {
//    spi__init(SPI_CLKDIV_4);
//    spi__double_speed__set(1);
//    enc28j60_select__init();

    console__init();
    stdout = &usart_out;
    console__run();
}
