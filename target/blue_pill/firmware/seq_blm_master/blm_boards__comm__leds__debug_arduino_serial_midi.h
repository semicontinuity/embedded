// Debugs LED update commands by sending them over serial port as MIDI.
// Format: [8m] [0l] [rg], where
// m: matrix (0-f)
// l: led (0-f)
// r: red (0-1)
// g: green (0-1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "multi_blm_leds_buffer__scanner__callbacks.h"

static HardwareSerial *blm_boards_leds__comm__serial;

void blm_boards__comm__leds__debug_arduino_serial_midi__init(HardwareSerial *serial) {
    blm_boards_leds__comm__serial = serial;
}

void blm_boards__comm__leds__debug_arduino_serial_midi__update_one(uint8_t matrix, uint8_t led, uint8_t r, uint8_t g) {
    r = r ? 1 : 0;
    g = g ? 1 : 0;
    blm_boards_leds__comm__serial->write(0x80 + matrix);
    blm_boards_leds__comm__serial->write(led);
    blm_boards_leds__comm__serial->write((r << 4U) + g);
}