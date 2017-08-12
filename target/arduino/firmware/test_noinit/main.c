// =============================================================================
// Tests noinit section
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

uint8_t pin_number __attribute__((section(".noinit")));

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
    LCDstring_of_flash(PSTR("data: "), 0, 0);

    LCDdata(pin_number);
    ++pin_number;

    while (1) {
    }
}

