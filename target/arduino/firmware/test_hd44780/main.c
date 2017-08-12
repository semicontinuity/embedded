#include "cpu/avr/gpio.h"
#include "LCD.h"          //Хедер для LCD дисплея
#include "prototip_fun.h" //Прототипы функций

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>//Хедер прерываний. 

#include <stdlib.h>


int main(void) {
    ENABLE_PULLUP(UNUSED_B4);
    ENABLE_PULLUP(UNUSED_B5);

    ENABLE_PULLUP(UNUSED_C0);
    ENABLE_PULLUP(UNUSED_C1);
    ENABLE_PULLUP(UNUSED_C2);
    ENABLE_PULLUP(UNUSED_C3);
    ENABLE_PULLUP(UNUSED_C4);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);
    ENABLE_PULLUP(UNUSED_D5);
    ENABLE_PULLUP(UNUSED_D6);
    ENABLE_PULLUP(UNUSED_D7);

    init();

    LCDstring_of_flash(PSTR("Parameter 1"), 0, 0);
    LCDstring_of_flash(PSTR("Parameter 2"), 0, 1);
    LCDstring_of_flash(PSTR("Parameter 3"), 0, 2);
    LCDstring_of_flash(PSTR("Parameter 4"), 0, 3);
	        
    while(1) {
        LCDstring_of_flash(PSTR("12.4"), 16, 0);
        LCDstring_of_flash(PSTR("27.7"), 16, 1);
        LCDstring_of_flash(PSTR("23.5"), 16, 2);
        LCDstring_of_flash(PSTR("65.1"), 16, 3);
        _delay_ms(1000);

        LCDstring_of_flash(PSTR("54.7"), 16, 0);
        LCDstring_of_flash(PSTR("67.5"), 16, 1);
        LCDstring_of_flash(PSTR("26.2"), 16, 2);
        LCDstring_of_flash(PSTR("34.5"), 16, 3);
        _delay_ms(1000);
    }
}

