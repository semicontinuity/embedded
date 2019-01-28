#include "cpu/avr/gpio.h"

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <stdlib.h>


int main(void) {
    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    ENABLE_PULLUP(IN__BUTTON5);
    ENABLE_PULLUP(IN__BUTTON6);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    led1__init();
    led2__init();
    led3__init();

    while(1) {
        uint8_t state = IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN) | _BV(IN__BUTTON5__PIN) | _BV(IN__BUTTON6__PIN));

        if (!(state & _BV(IN__BUTTON1__PIN))) {
            led1__set(1);
            led2__set(0);
            led3__set(0);
        } else if (!(state & _BV(IN__BUTTON2__PIN))) {
            led1__set(0);
            led2__set(1);
            led3__set(0);
        } else if (!(state & _BV(IN__BUTTON3__PIN))) {
            led1__set(1);
            led2__set(1);
            led3__set(0);
        } else if (!(state & _BV(IN__BUTTON4__PIN))) {
            led1__set(0);
            led2__set(0);
            led3__set(1);
        } else if (!(state & _BV(IN__BUTTON5__PIN))) {
            led1__set(1);
            led2__set(0);
            led3__set(1);
        } else if (!(state & _BV(IN__BUTTON6__PIN))) {
            led1__set(0);
            led2__set(1);
            led3__set(1);
        } else {
            led1__set(0);
            led2__set(0);
            led3__set(0);
        }

        _delay_ms(50);
    }
}

