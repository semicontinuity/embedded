// =============================================================================
// Tests USART
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"


#include "cpu/avr/gpio.h"
#include "LCD.h"          //Хедер для LCD дисплея
#include "prototip_fun.h" //Прототипы функций

#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"


static void application__init(void) {
    usart0__init();

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

static void application__start(void) {
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}


int main(void) {
    application__init();
    application__start();

    char i = 0;
    for(;;) {
        uint8_t c = usart0__in__read();
        led1__set(i);
        i = 1 - i;
        LCDdata(c);
        usart0__out__write(c);
    }
    return 0;
}

