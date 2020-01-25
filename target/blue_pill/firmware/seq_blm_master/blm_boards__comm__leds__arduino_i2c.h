// Sends LED update commands to BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>


static TwoWire *blm_boards__comm__arduino_i2c__wire;
static uint8_t blm_boards__comm__arduino_i2c__base_address;


void blm_boards__comm__leds__arduino_i2c__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm__arduino_i2c__wire = wire;
    blm_boards__comm__arduino_i2c__base_address = base_address;
}


void blm_boards__comm__leds__arduino_i2c__update_one(
    uint8_t board,
    uint8_t led,
    uint8_t r,
    uint8_t g,
    uint8_t b)
{
    blm_boards__comm__arduino_i2c__wire->beginTransmission(blm_boards__comm__arduino_i2c__base_address + board);
    blm_boards__comm__arduino_i2c__wire->write(led);
    blm_boards__comm__arduino_i2c__wire->write(r);
    blm_boards__comm__arduino_i2c__wire->write(g);
    blm_boards__comm__arduino_i2c__wire->write(b);
    blm_boards__comm__arduino_i2c__wire->endTransmission();
}
