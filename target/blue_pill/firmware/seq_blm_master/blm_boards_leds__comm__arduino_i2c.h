// Sends LED update commands to BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "blm_boards_leds__state_scanner_callbacks.h"


TwoWire Wire2(2);


void blm_boards_leds__comm__init() {
    Wire2.begin();
}


void blm_boards_leds__state_scanner__scan__update_one(
    uint8_t board,
    uint8_t led,
    uint8_t r,
    uint8_t g,
    uint8_t b)
{
    Wire2.beginTransmission(0x30 + board);
    Wire2.write(led);
    Wire2.write(r);
    Wire2.write(g);
    Wire2.write(b);
    Wire2.endTransmission();
}
