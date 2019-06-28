#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/display/hd44780/hd44780.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include <stdlib.h>
#include <stdint.h>


int main(void) {
    hd44780_lcd__init();
    hd44780_lcd__send_data('A');
    //hd44780_lcd__write_string_xy_P(PSTR("Hello, world!"), 0, 0);

    while(1) {
    }
}

