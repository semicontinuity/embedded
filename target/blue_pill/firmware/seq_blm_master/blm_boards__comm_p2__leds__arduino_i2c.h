// Sends LED update commands to BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>


static TwoWire *blm_boards__comm_p2__leds__arduino_i2c__wire;
static uint8_t blm_boards__comm_p2__leds__arduino_i2c__base_address;


void blm_boards__comm_p2__leds__arduino_i2c__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm_p2__leds__arduino_i2c__wire = wire;
    blm_boards__comm_p2__leds__arduino_i2c__base_address = base_address;
}

// Implements blm_boards__comm_p2__leds__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p2__leds__arduino_i2c__emit_command(uint8_t board, uint8_t command) {
    if (board < BLM_SCALAR_NUM_BOARDS) {
        blm_boards__comm_p2__leds__arduino_i2c__wire->beginTransmission(blm_boards__comm_p2__leds__arduino_i2c__base_address + board);
        blm_boards__comm_p2__leds__arduino_i2c__wire->write(command);
        blm_boards__comm_p2__leds__arduino_i2c__wire->endTransmission();
    }
}