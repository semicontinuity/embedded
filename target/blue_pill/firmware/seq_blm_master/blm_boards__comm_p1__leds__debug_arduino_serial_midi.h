// Debugs LED update commands by sending them over serial port as MIDI.
// Format: [8m] [0l] [rg], where
// m: matrix (0-f)
// l: led (0-f)
// r: red (0-1)
// g: green (0-1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_boards__comm_p1__leds__buffer__scanner__callbacks.h"

static HardwareSerial *blm_boards__comm_p1__leds__debug_arduino_serial;

void blm_boards__comm_p1__leds__debug_arduino_serial_midi__init(HardwareSerial *serial) {
    blm_boards__comm_p1__leds__debug_arduino_serial = serial;
}

void blm_boards__comm_p1__leds__debug_arduino_serial_midi__update_one(uint8_t matrix, uint8_t led, uint8_t r, uint8_t g) {
    r = r ? 1 : 0;
    g = g ? 1 : 0;
    blm_boards__comm_p1__leds__debug_arduino_serial->write(0x80 + matrix);
    blm_boards__comm_p1__leds__debug_arduino_serial->write(led);
    blm_boards__comm_p1__leds__debug_arduino_serial->write((r << 4U) + g);
}