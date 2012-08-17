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
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();
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
