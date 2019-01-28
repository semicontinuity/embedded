#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/display/hd44780/hd44780.h"

#include "util/hex.h"
#include "temperature.h"

#include "cpu/avr/util/bcd.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h> 

#include <stdlib.h>
#include <stdint.h>


void display__print_byte_as_hex(const int16_t value) {
    hd44780_lcd__send_data(value >> 8);
    hd44780_lcd__send_data(value & 0xFF);
}

void display__print_separator(void) {
    hd44780_lcd__send_data(':');
}

uint16_t as_two_hex_chars(const uint8_t value) {
    uint8_t hn = (value >> 4);
    uint8_t hc = hn + (hn < 10 ? '0' : ('A' - 10));
    uint8_t ln = (value & 0x0F);
    uint8_t lc = ln + (ln < 10 ? '0' : ('A' - 10));
    return (hc<<8) | lc;
}


void display__print_temperature(void) {
    display__print_byte_as_hex(as_two_hex_chars(id[0]));
    display__print_byte_as_hex(as_two_hex_chars(id[1]));
    display__print_separator();

    display__print_byte_as_hex(as_two_hex_chars(id[2]));
    display__print_byte_as_hex(as_two_hex_chars(id[3]));
    display__print_separator();

    display__print_byte_as_hex(as_two_hex_chars(id[4]));
    display__print_byte_as_hex(as_two_hex_chars(id[5]));
    display__print_separator();

    display__print_byte_as_hex(as_two_hex_chars(id[6]));
    display__print_byte_as_hex(as_two_hex_chars(id[7]));
}


int main(void) {
    led1__init();
    led2__init();
    led3__init();

    ENABLE_PULLUP(UNUSED_B4);

    ENABLE_PULLUP(UNUSED_C0);
    ENABLE_PULLUP(UNUSED_C1);
    ENABLE_PULLUP(UNUSED_C2);
    ENABLE_PULLUP(UNUSED_C3);
    ENABLE_PULLUP(UNUSED_C4);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    hd44780_lcd__init();
    hd44780_lcd__write_string_xy_P(PSTR("Searching devices..."), 0, 0);

    start_OW();
    _delay_ms(750);

    led1__set(1);
    temperature_init();
    led1__set(0);

    hd44780_lcd__goto(0, 3);
    display__print_temperature();

    while(1) {
    }
}

