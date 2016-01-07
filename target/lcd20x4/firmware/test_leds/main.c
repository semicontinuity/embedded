// =============================================================================
// Tests LEDs and 1-wire pin
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/comm/onewire__bus.h"


#include "cpu/avr/gpio.h"
#include "LCD.h"          //Хедер для LCD дисплея
#include "prototip_fun.h" //Прототипы функций

#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


static void application__init(void) {
    onewire__bus__init();
    led1__init();
    led2__init();
    led3__init();

    ENABLE_PULLUP(UNUSED_B4);
    ENABLE_PULLUP(UNUSED_B5);

    ENABLE_PULLUP(UNUSED_C0);
    ENABLE_PULLUP(UNUSED_C1);
    ENABLE_PULLUP(UNUSED_C2);
    ENABLE_PULLUP(UNUSED_C3);
    ENABLE_PULLUP(UNUSED_C4);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    init();
}


int main(void) {
    application__init();

    while (1) {
        led1__set(1);
        LCDstring_of_flash(PSTR("L1"), 0, 0);
        _delay_ms(1000);
        led1__set(0);

        led2__set(1);
        LCDstring_of_flash(PSTR("L2"), 0, 0);
        _delay_ms(1000);
        led2__set(0);

        led3__set(1);
        LCDstring_of_flash(PSTR("L3"), 0, 0);
        _delay_ms(1000);
        led3__set(0);

        onewire__bus__set(0);
        LCDstring_of_flash(PSTR("OW"), 0, 0);
        _delay_ms(1000);
        onewire__bus__set(1);
    }
}

