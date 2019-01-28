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
    LCDstring_of_flash(PSTR("Buttons test"), 0, 0);
    LCDstring_of_flash(PSTR("--------------------"), 0, 1);
    LCDstring_of_flash(PSTR("Pressed:"), 0, B_Y);

    while(1) {
        uint8_t state = IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN) | _BV(IN__BUTTON5__PIN) | _BV(IN__BUTTON6__PIN));

        LCDstring_of_flash(state & _BV(IN__BUTTON1__PIN) ? PSTR("_") : PSTR("1"), B1_X, B_Y);
        LCDstring_of_flash(state & _BV(IN__BUTTON2__PIN) ? PSTR("_") : PSTR("2"), B2_X, B_Y);
        LCDstring_of_flash(state & _BV(IN__BUTTON3__PIN) ? PSTR("_") : PSTR("3"), B3_X, B_Y);
        LCDstring_of_flash(state & _BV(IN__BUTTON4__PIN) ? PSTR("_") : PSTR("4"), B4_X, B_Y);
        LCDstring_of_flash(state & _BV(IN__BUTTON5__PIN) ? PSTR("_") : PSTR("5"), B5_X, B_Y);
        LCDstring_of_flash(state & _BV(IN__BUTTON6__PIN) ? PSTR("_") : PSTR("6"), B6_X, B_Y);
        _delay_ms(50);
    }
}

