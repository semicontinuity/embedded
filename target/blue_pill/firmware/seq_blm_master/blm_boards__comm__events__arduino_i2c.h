// Reads button and encoder events from BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>


static TwoWire *blm_boards__comm__events__arduino_i2c__wire;
static uint8_t blm_boards__comm__events__arduino_i2c__base_address;


void blm_boards__comm__events__arduino_i2c__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm__events__arduino_i2c__wire = wire;
    blm_boards__comm__events__arduino_i2c__base_address = base_address;
}

uint8_t blm_boards__comm__events__arduino_i2c__events__read(uint8_t board) {
    blm_boards__comm__events__arduino_i2c__wire->requestFrom(blm_boards__comm__events__arduino_i2c__base_address + board, 1);
    return blm_boards__comm__events__arduino_i2c__wire->read();
}
