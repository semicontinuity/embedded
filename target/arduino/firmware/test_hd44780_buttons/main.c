#include "cpu/avr/gpio.h"
#include "LCD.h"         
#include "prototip_fun.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <stdlib.h>
#include <stdlib.h>


int main(void) {
    ENABLE_PULLUP(UNUSED_B4);
    ENABLE_PULLUP(UNUSED_B5);

    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    ENABLE_PULLUP(IN__BUTTON5);
    ENABLE_PULLUP(IN__BUTTON6);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);
    ENABLE_PULLUP(UNUSED_D5);
    ENABLE_PULLUP(UNUSED_D6);
    ENABLE_PULLUP(UNUSED_D7);

    init();

    while(1) {
        uint8_t state = IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN) | _BV(IN__BUTTON5__PIN) | _BV(IN__BUTTON6__PIN));

        if (state & _BV(IN__BUTTON1__PIN)) {
            LCDstring_of_flash(PSTR("1"), 0, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 0, 0);
        }

        if (state & _BV(IN__BUTTON2__PIN)) {
            LCDstring_of_flash(PSTR("2"), 1, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 1, 0);
        }

        if (state & _BV(IN__BUTTON3__PIN)) {
            LCDstring_of_flash(PSTR("3"), 2, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 2, 0);
        }

        if (state & _BV(IN__BUTTON4__PIN)) {
            LCDstring_of_flash(PSTR("4"), 3, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 3, 0);
        }

        if (state & _BV(IN__BUTTON5__PIN)) {
            LCDstring_of_flash(PSTR("5"), 4, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 4, 0);
        }

        if (state & _BV(IN__BUTTON6__PIN)) {
            LCDstring_of_flash(PSTR("6"), 5, 0);
        } else {
            LCDstring_of_flash(PSTR("_"), 5, 0);
        }

        _delay_ms(50);
    }
}

