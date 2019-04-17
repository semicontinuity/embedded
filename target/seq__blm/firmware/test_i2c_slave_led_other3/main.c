//#include "drivers/out/led1.h"
#include "I2CSlave.h"
#include <util/delay.h>

#define I2C_ADDR 0x1F

volatile uint8_t data;


void I2C_received(uint8_t received_data) {
//    led1__toggle();
    data = received_data;
}


void I2C_requested(void) {
    I2C_transmitByte(data);
}


void setup(void) {
    // set received/requested callbacks
    I2C_setCallbacks(I2C_received, I2C_requested);

    // init I2C
    PORTC |= ((1 << PINC4) | (1 << PINC5));
    TWDR = 0;
    I2C_init(I2C_ADDR);
}


int main(void) {
    _delay_ms(100);
//    led1__init();
    setup();
    while (1) {
//        _delay_ms(100);
//        led1__toggle();
    }
}