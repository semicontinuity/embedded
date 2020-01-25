// Sends LED update commands to BLM boards with I2C.
// NB: Arduino I2C API is blocking, so communication will consume some time!
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "leds__buffer__scanner__callbacks.h"


TwoWire Wire2(2);


void blm_boards__comm__init() {
    Wire2.begin();
}

uint8_t blm_boards__comm__events__read() {
    return 0;
}

void blm_boards__comm__leds__update_one(
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
