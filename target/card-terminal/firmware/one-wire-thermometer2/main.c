// =============================================================================
// 1-wire thermometer.
// The bus is implemented with one external pull-up, using pin bit-banging.
//
// Does not work, because FET master circuit is not fast enough.
// =============================================================================

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"
#include "cpu/avr/util/bcd.h"
#include "util/hex.h"
#include "temperature.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdint.h>


uint8_t const FRACTIONS[] = {
    '0', // 0/10 = 0.0000
    '1', // 1/10 = 0.0625
    '1', // 2/10 = 0.1250
    '2', // 3/10 = 0.1875
    '3', // 4/10 = 0.2500
    '3', // 5/10 = 0.3125
    '4', // 6/10 = 0.3750
    '4', // 7/10 = 0.4375
    '5', // 8/10 = 0.5000
    '6', // 9/10 = 0.5625
    '6', // A/10 = 0.6250
    '7', // B/10 = 0.6875
    '8', // C/10 = 0.7500
    '8', // D/10 = 0.8125
    '9', // E/10 = 0.8750
    '9', // F/10 = 0.9375
};


void terminal__print_hex(const uint8_t value) {
    const uint16_t string = byte__to_hex_string(value);
    const uint8_t h = string >> 8;
    const uint8_t l = string & 0xFF;
    terminal__putc(h);
    terminal__putc(l);
}

void terminal__print_bcd(const uint8_t value) {
    const uint8_t h = value >> 4;
    terminal__putc(h ? h + '0' : ' ');
    terminal__putc((value & 0x0F) + '0');
}

void terminal__print_temperature(const uint16_t value) {
    uint8_t bcd = uint8_to_bcd(value >> 8);
    terminal__print_bcd(bcd);
    terminal__putc('.');
    terminal__putc(FRACTIONS[(value & 0xFF) >> 4]);
}


uint16_t bcd_to_chars(const uint8_t value) {
    const uint8_t h = value >> 4;
    uint8_t hc = h ? h + '0' : ' ';
    uint8_t lc = (value & 0x0F) + '0';
    return (hc<<8) | lc;
}

void display__print_temperature(const uint16_t value, const uint8_t x, const uint8_t y) {
    uint8_t bcd = uint8_to_bcd(value >> 8);
    uint16_t i_chars = bcd_to_chars(bcd);
    uint8_t f_chars = FRACTIONS[(value & 0xFF) >> 4];

    LCDG_SendSymbol(x + 0, y, i_chars >> 8);
    LCDG_SendSymbol(x + 1, y, i_chars & 0xFF);
    LCDG_SendSymbol(x + 2, y, '.');
    LCDG_SendSymbol(x + 3, y, f_chars);
}




int main(int argc, char **argv) {

    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    // clock prescaler 1
    CLKPR = 0x80;
    CLKPR = 0x00;

    // backlight ON
//    DDRD |= (1<<0);
//    PORTD |= (1<<0);

    // RTS=0
    DDRD |= (1<<6);
    PORTD &= ~(1<<6);


    LCDG_InitPort();
    _delay_ms(30);
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

//    terminal__init();

    LCDG_SendString(0, 1, "Подвал:");
    LCDG_SendString(0, 2, "Бункер:");


    while(1) {
        start_OW();
        _delay_ms(750);
        lese_Temperatur();
        display__print_temperature(ow_array[0], 8, 1);
        display__print_temperature(ow_array[1], 8, 2);
    }

    return 0;
}
