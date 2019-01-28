#include <util/delay.h>

#include "cpu/avr/gpio.h"
//#include "cpu/avr/usart0.h"

#include <avr/wdt.h>


#include "output.h"
#include "sensors.h"


int main(void) {
    wdt_enable(WDTO_1S);

    sensors_a__init();
    sensors_b__init();

    output__init();

/*
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
*/

    while(1) {
        wdt_reset();
        _delay_loop_2(80);

        if (sensors_a__get() || sensors_b__get())
            output__on();
        else
            output__off();
    }
}
