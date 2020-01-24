// Debugs LED update commands by sending them over serial port as MIDI.
// Format: [8m] [0l] [rg], where
// m: matrix (0-f)
// l: led (0-f)
// r: red (0-1)
// g: green (0-1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_boards_leds__state_scanner_callbacks.h"


void blm_boards_leds__state_scanner__scan__update_one(
        uint8_t matrix,
        uint8_t led,
        uint8_t r,
        uint8_t g,
        uint8_t b)
{
    r = r ? 1 : 0;
    g = g ? 1 : 0;
    Serial2.write(0x80 + matrix);
    Serial2.write(led);
    Serial2.write((r << 4U) + g);
}
