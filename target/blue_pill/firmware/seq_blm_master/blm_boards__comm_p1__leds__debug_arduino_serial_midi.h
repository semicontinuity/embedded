// Debugs LED update commands by sending them over serial port as MIDI.
// Format: [8m] [0l] [rg], where
// m: matrix (0-f)
// l: led (0-f)
// r: red (0-1)
// g: green (0-1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "debug_midi__arduino_serial.h"


// Implements blm_boards__comm_p1__leds__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p1__leds__debug_arduino_serial_midi__update_one(uint8_t matrix, uint8_t led, uint8_t r, uint8_t g) {
    r = r ? 1 : 0;
    g = g ? 1 : 0;
    debug_midi__note_off(matrix, led, (r << 4U) + g);
}