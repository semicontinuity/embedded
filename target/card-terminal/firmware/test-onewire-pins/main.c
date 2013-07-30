// =============================================================================
// Tests external 1-wire and smart card hardware.
// Jumper JP1 must be installed.
//
// When RTS is 1, data bus is shorted to ground,
// otherwise the signal asserted on TX pin must be read on RX pin.
// =============================================================================
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"

#include <stdbool.h>
#include <stdint.h>


void print_result(const char *test_name, bool result) {
    terminal__putc('\n');
    terminal__print_P(test_name);
    terminal__print_P(result ? PSTR(" OK") : PSTR(" FAIL"));
}


void rts(uint8_t v) {
    if (v) PORTD |= (1<<6); else PORTD &= ~(1<<6);
}

void tx(uint8_t v) {
    if (v) PORTD |= (1<<3); else PORTD &= ~(1<<3);
}

uint8_t rx(void) {
    return PIND & (1<<2);
}


bool test_1(void) {
    rts(0);
    tx(0);
    _delay_us(1);
    return rx() == 0;
}

bool test_2(void) {
    rts(0);
    tx(1);
    _delay_us(1);
    return rx() != 0;
}

bool test_3(void) {
    rts(1);
    tx(0);
    _delay_us(1);
    return rx() == 0;
}

bool test_4(void) {
    rts(1);
    tx(1);
    _delay_us(1);
    return rx() == 0;
}


int main(int argc, char **argv) {

    // backlight on
    DDRD |= (1<<0);
    PORTD |= (1<<0);

    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();
    terminal__init();
    
    // TX as out
    DDRD |= (1<<3);

    // RTS as out
    DDRD |= (1<<6);

    print_result(PSTR("RTS=0 TX=0 RX=0"), test_1());
    print_result(PSTR("RTS=0 TX=1 RX=1"), test_2());
    print_result(PSTR("RTS=1 TX=0 RX=0"), test_3());
    print_result(PSTR("RTS=1 TX=1 RX=0"), test_4());

    while(1);
    return 0;
}
