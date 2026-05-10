#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "util/bitops.h"

#include "cpu/avr/spi.h"

#include "cpu/avr/util/bcd.h"
#include "cpu/avr/util/mult16x16.h"
#include "cpu/avr/drivers/display/segment/static2_spi.h"

#include "console_service.h"


inline static void hygrometer__init(void) {
    // Reference voltage at AVCC+AREF, no left adjustment, ADC0.
    ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX0);

    // ADC Enable,  division factor 64
    ADCSRA = (1 << ADEN) | (6 << ADPS0);
}


inline static uint16_t hygrometer__read(void) {
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    return U16(ADCL, ADCH);
}


inline static void hygrometer__run(void) {
    for(;;) {
        uint16_t hygrometer_value = hygrometer__read() - HUMIDITY_OFFSET;
        uint16_t multiplier = (uint16_t)HUMIDITY_MULTIPLIER;
        uint16_t humidity;
        MultiU16X16toH16(humidity, hygrometer_value, multiplier);

        display__render_bcd((uint8_t) uint9_to_bcd(humidity));
        _delay_ms(DELAY);
    }
}


int main(void) {

    ENABLE_PULLUP(DEBUG_JUMPER);
    _delay_ms(50);
    
    hygrometer__init();

    spi__init(SPI_CLKDIV_16);
    display__init();
    display__on();

    if (IS_1(DEBUG_JUMPER)) 
        hygrometer__run();
    else {
        console_service__init();
        console_service__run();
    }

    return 0;
}
