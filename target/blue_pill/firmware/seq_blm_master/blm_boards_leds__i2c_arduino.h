#include <Wire.h>
#include <stdint.h>
#include "blm_boards_leds.h"

TwoWire Wire2(2);


void blm_boards_leds__init() {
//    Wire2.begin();
}


void blm_boards_leds__update_one(
        uint8_t matrix_x,
        uint8_t matrix_y,
        uint8_t local_x,
        uint8_t local_y,
        uint8_t r,
        uint8_t g,
        uint8_t b)
{
/*
    Wire2.beginTransmission(0x30 + (matrix_y << 2U) + matrix_x);
    Wire2.write((local_x << 2U) + local_y);
    Wire2.write(r);
    Wire2.write(g);
    Wire2.write(b);
    Wire2.endTransmission();
*/
}
