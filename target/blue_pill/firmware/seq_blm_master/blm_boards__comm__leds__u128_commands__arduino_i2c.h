// Sends UNPACK128 LED update commands to BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "seq_blm_bridge__config.h"


static TwoWire *blm_boards__comm__leds__u128_commands__arduino_i2c__wire;
static uint8_t blm_boards__comm__leds__u128_commands__arduino_i2c__base_address;


void blm_boards__comm__leds__u128_commands__arduino_i2c__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm__leds__u128_commands__arduino_i2c__wire = wire;
    blm_boards__comm__leds__u128_commands__arduino_i2c__base_address = base_address;
}

void blm_boards__comm__leds__u128_commands__arduino_i2c__emit_command(uint8_t board, uint8_t led, uint8_t color) {
    if (board < NUM_BOARDS) {
        // UNPACK128 message, format [ 01 ] [DIR : 1] [ REFRESH : 1] [ LED : 4] + [ RESERVED: 1] [ INDEX : 7 ]
        blm_boards__comm__leds__u128_commands__arduino_i2c__wire->beginTransmission(blm_boards__comm__leds__u128_commands__arduino_i2c__base_address + board);
        blm_boards__comm__leds__u128_commands__arduino_i2c__wire->write(0x50 + led);
        blm_boards__comm__leds__u128_commands__arduino_i2c__wire->write(color);
        blm_boards__comm__leds__u128_commands__arduino_i2c__wire->endTransmission();
    }
}
