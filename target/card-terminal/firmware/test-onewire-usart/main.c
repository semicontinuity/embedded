// =============================================================================
// Tests external 1-wire and smart card hardware.
// Jumper JP1 must be installed.
//
// The data sent by USART should be received back.
// =============================================================================

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"

#include <stdbool.h>
#include <stdint.h>

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"


void print_result(const char *test_name, bool result) {
    terminal__putc('\n');
    terminal__print_P(test_name);
    terminal__print_P(result ? PSTR(" OK") : PSTR(" FAIL"));
}


bool test(char c) {
    usart0__out__write(c);
    return usart0__in__read() == c;
}


int main(int argc, char **argv) {

    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    // clock prescaler 1
    CLKPR = 0x80;
    CLKPR = 0x00;

    // backlight on
    DDRD |= (1<<0);
    PORTD |= (1<<0);

    // 0 -> RTS
    DDRD |= (1<<6);
    PORTD &= ~(1<<6);

    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();
    terminal__init();


    usart0__init();
    usart0__out__enabled__set();
    usart0__in__enabled__set();

    usart0__rate__set(USART_BAUD_RATE);
    print_result(PSTR("echo at   9600"), test('a'));
    print_result(PSTR("echo at 115200"), test(115200));
    print_result(PSTR("write/read 'c'"), test('c'));
    print_result(PSTR("write/read 'd'"), test('d'));

    while(1);
    return 0;
}
