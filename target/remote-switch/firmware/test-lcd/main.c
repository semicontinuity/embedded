#include "drivers/lcd__backlight.h"
#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include "cpu/avr/gpio.h"
#include "LCD.h"          
#include "prototip_fun.h" 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <stdlib.h>


int main(void) {
//    USE_AS_OUTPUT(LCD__BACKLIGHT);

    ENABLE_PULLUP(UNUSED_C0);
    ENABLE_PULLUP(UNUSED_C1);
    ENABLE_PULLUP(UNUSED_C2);
    ENABLE_PULLUP(UNUSED_C3);
    ENABLE_PULLUP(UNUSED_C4);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);
    ENABLE_PULLUP(UNUSED_D2);
    ENABLE_PULLUP(UNUSED_D3);
    ENABLE_PULLUP(UNUSED_D4);
    ENABLE_PULLUP(UNUSED_D5);

    led1__init();
    led2__init();
    led3__init();
    led4__init();
    lcd__backlight__init();

    led1__set(1);
    led2__set(1);
    led3__set(1);
    led4__set(1);
    lcd__backlight__set(1);

    init();


    LCDstring_of_flash(PSTR("Hello"), 0, 0);
    LCDstring_of_flash(PSTR("world"), 0, 1);
	        
    while(1) {
        OUT_1(LCD__BACKLIGHT);
        _delay_ms(1000);

        OUT_0(LCD__BACKLIGHT);
        _delay_ms(1000);
    }
}

