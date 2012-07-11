#include "device.h"
//#include "debug.h"
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"

#include <avr/wdt.h>


int main(void)
{
    wdt_enable (WDTO_1S);
    // pullups on all inputs, output will be driven high initially
    PORTC = 0xFF;
    PORTD = 0xFF;
    PORTB = 0xFF;


    sensors_a_init();
    sensors_b_init();

    CONFIGURE_AS_OUTPUT(SENSOR);

    CONFIGURE_AS_OUTPUT(UART_TX);

    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();


    while(1)
    {
        wdt_reset();
/*
        debug_putc('[');
        debug_putc(']');

        print_byte_as_hex(0x5A);
*/
        _delay_loop_2(80);
        usart__out__write('.');

//        if (sensors_a_active()) uart_transmit_char_polled('A'); else uart_transmit_char_polled('a');
//        if (sensors_b_active()) uart_transmit_char_polled('B'); else uart_transmit_char_polled('b');

        if (sensors_a_active() || sensors_b_active())
            DRIVE_HIGH(SENSOR);
        else
            DRIVE_LOW(SENSOR);

    }

}
