#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"
#include "LCD.h"         
#include "prototip_fun.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "util/hex.h"
#include "temperature.h"

#include "cpu/avr/util/bcd.h"

#include <stdlib.h>


static void application__init(void) {
    led1__init();
    led2__init();
    led3__init();

    ENABLE_PULLUP(UNUSED_B4);

    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    ENABLE_PULLUP(IN__BUTTON5);
    ENABLE_PULLUP(IN__BUTTON6);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    init();
}


int main(void) {
    led1__set(1);
    application__init();
    led2__set(1);

    LCDstring_of_flash(PSTR("Temperature"), 0, 0);
    LCDstring_of_flash(PSTR("--------------------"), 0, 1);

    while(1) {
       led3__toggle();
        start_OW();
        _delay_ms(750);


        if (lese_Temperatur()) {
            LCDstring_of_flash(PSTR("CRC error"), 0, 3);
        } else {
            LCDstring_of_flash(PSTR("OK       "), 0, 3);
            display__print_temperature(ow_array[0], 0, 0);
        }
        
    }
}

