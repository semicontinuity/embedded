#include "drivers/out/led1.h"
#include "I2CSlave.h"

#define I2C_ADDR 0x10

volatile uint8_t data;


void I2C_received(uint8_t received_data) {
    led1__toggle();
    data = received_data;
}


void I2C_requested(void) {
    I2C_transmitByte(data);
}


void setup(void) {
    // set received/requested callbacks
    I2C_setCallbacks(I2C_received, I2C_requested);

    // init I2C
    I2C_init(I2C_ADDR);
}


int main(void) {
    led1__init();
    setup();
    while (1);
}