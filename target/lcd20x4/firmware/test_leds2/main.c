// =============================================================================
// Tests LEDs
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"

#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


static void application__init(void) {
    led1__init();
    led2__init();
    led3__init();
}


int main(void) {
    application__init();

    while (1) {
        led1__set(1);
        _delay_ms(1000);
        led1__set(0);

        led2__set(1);
        _delay_ms(1000);
        led2__set(0);

        led3__set(1);
        _delay_ms(1000);
        led3__set(0);
    }
}

