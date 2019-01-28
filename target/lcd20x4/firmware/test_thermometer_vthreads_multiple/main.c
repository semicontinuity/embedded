// =============================================================================
// Thermometer.
// Reads DS18B20 sensor using vthreads-based driver.
// =============================================================================

#include "globals.c"

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"

#include "cpu/avr/gpio.h"
#include "LCD.h"
#include "prototip_fun.h"

#include "drivers/comm/onewire.h"
#include "drivers/comm/onewire__bus.h"
#include "services/temperature_reader.h"
#include "cpu/avr/util/bcd.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <stdlib.h>
#include <stdint.h>

uint8_t const FRACTIONS[] = {
    '0', // 0/10 = 0.0000
    '1', // 1/10 = 0.0625
    '1', // 2/10 = 0.1250
    '2', // 3/10 = 0.1875
    '3', // 4/10 = 0.2500
    '3', // 5/10 = 0.3125
    '4', // 6/10 = 0.3750
    '4', // 7/10 = 0.4375
    '5', // 8/10 = 0.5000
    '6', // 9/10 = 0.5625
    '6', // A/10 = 0.6250
    '7', // B/10 = 0.6875
    '8', // C/10 = 0.7500
    '8', // D/10 = 0.8125
    '9', // E/10 = 0.8750
    '9', // F/10 = 0.9375
};

uint16_t bcd_to_chars(const uint8_t value) {
    const uint8_t h = value >> 4;
    uint8_t hc = h ? h + '0' : ' ';
    uint8_t lc = (value & 0x0F) + '0';
    return (hc<<8) | lc;
}

uint16_t as_two_hex_chars(const uint8_t value) {
    uint8_t hn = (value >> 4);
    uint8_t hc = hn + (hn < 10 ? '0' : ('A' - 10));
    uint8_t ln = (value & 0x0F);
    uint8_t lc = ln + (ln < 10 ? '0' : ('A' - 10));
    return (hc<<8) | lc;
}

void display__print_temperature(const uint16_t value, const uint8_t x, const uint8_t y) {
    LCDGotoXY(x,y);

    uint8_t h = (uint8_t)(((uint16_t)value) >> 8);
    uint8_t l = (uint8_t)(((uint16_t)value) & 0xFF);

    uint16_t h_chars = as_two_hex_chars(h);
    LCDdata(h_chars >> 8);
    LCDdata(h_chars & 0xFF);

    uint16_t l_chars = as_two_hex_chars(l);
    LCDdata(l_chars >> 8);
    LCDdata(l_chars & 0xFF);

    LCDdata('=');

    uint8_t bcd = uint8_to_bcd(value >> 8);
    uint16_t i_chars = bcd_to_chars(bcd);
    uint8_t f_chars = FRACTIONS[(value & 0xFF) >> 4];

    LCDdata(i_chars >> 8);
    LCDdata(i_chars & 0xFF);
    LCDdata('.');
    LCDdata(f_chars);
}


void temperature_reader__readings__on_changed(void) {
#if DS18X20_SENSOR_COUNT >= 1
     display__print_temperature(temperature_reader__readings[0], 0, 0);
#endif
#if DS18X20_SENSOR_COUNT >= 2
     display__print_temperature(temperature_reader__readings[1], 0, 1);
#endif
}


int main(void) {
    led1__init();
    led2__init();
    led3__init();

    ENABLE_PULLUP(UNUSED_B4);

    ENABLE_PULLUP(UNUSED_C0);
    ENABLE_PULLUP(UNUSED_C1);
    ENABLE_PULLUP(UNUSED_C2);
    ENABLE_PULLUP(UNUSED_C3);
    ENABLE_PULLUP(UNUSED_C4);
    ENABLE_PULLUP(UNUSED_C5);

    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);

    init();
    onewire__bus__init();
    onewire__thread__init();
    temperature_reader__thread__start();

    sei();

    for(;;) {
        if (temperature_reader__thread__is_runnable()) {
            temperature_reader__thread__run();
        }
    }
}

