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


uint16_t as_two_hex_chars(const uint8_t value) {
    uint8_t hn = (value >> 4);
    uint8_t hc = hn + (hn < 10 ? '0' : ('A' - 10));
    uint8_t ln = (value & 0x0F);
    uint8_t lc = ln + (ln < 10 ? '0' : ('A' - 10));
    return (hc<<8) | lc;
}

int main(void) {
    application__init();
    application__start();

    char i = 0;
    for(;;) {
        uint8_t c = usart0__in__read();
        led1__set(i);
        i = 1 - i;

        uint16_t chars = as_two_hex_chars(c);
        LCDdata(chars >> 8);
        LCDdata(chars & 0xFF);
    }
    return 0;
}

