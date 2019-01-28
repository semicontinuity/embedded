#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"
#include "LCD.h"          //Хедер для LCD дисплея
#include "prototip_fun.h" //Прототипы функций

#include "util/hex.h"
#include "temperature.h"

#include "cpu/avr/util/bcd.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>//Хедер прерываний. 

#include <stdlib.h>
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

uint16_t as_two_hex_chars(const uint8_t value) {
    uint8_t hc = (value >> 4) + '0';
    uint8_t lc = (value & 0x0F) + '0';
    return (hc<<8) | lc;
}

uint16_t bcd_to_chars(const uint8_t value) {
    const uint8_t h = value >> 4;
    uint8_t hc = h ? h + '0' : ' ';
    uint8_t lc = (value & 0x0F) + '0';
    return (hc<<8) | lc;
}

void display__print_temperature(const int16_t value, const uint8_t x, const uint8_t y) {
    LCDGotoXY(x,y);

    uint8_t h = (uint8_t)(((uint16_t)value) >> 8);
    uint8_t l = (uint8_t)(((uint16_t)value) & 0xFF);

    uint16_t h_chars = as_two_hex_chars(h);
    LCDdata(h_chars >> 8);
    LCDdata(h_chars & 0xFF);

    uint16_t l_chars = as_two_hex_chars(l);
    LCDdata(l_chars >> 8);
    LCDdata(l_chars & 0xFF);


    uint8_t bcd = uint8_to_bcd(value >> 8);
    uint16_t i_chars = bcd_to_chars(bcd);
    uint8_t f_chars = FRACTIONS[(value & 0xFF) >> 4];

    LCDdata('=');
    LCDdata(i_chars >> 8);
    LCDdata(i_chars & 0xFF);
    LCDdata('.');
    LCDdata(f_chars);
}


int main(void) {
    led1__init();
    led2__init();
    led3__init();

    ENABLE_PULLUP(UNUSED_B4);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    init();
    LCDstring_of_flash(PSTR("Temperature"), 0, 1);

    while(1) {
/*        start_OW();
        _delay_ms(750);

        led1__set(1);
        if (lese_Temperatur()) {
            LCDstring_of_flash(PSTR("CRC error"), 0, 3);
        } else {
            LCDstring_of_flash(PSTR("OK       "), 0, 3);
            display__print_temperature(ow_array[0], 0, 0);
        }
        
        led1__set(0);
*/
    }
}

