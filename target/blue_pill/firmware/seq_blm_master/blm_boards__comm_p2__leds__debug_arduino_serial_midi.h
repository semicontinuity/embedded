// Debugs LED update commands by sending them over serial port as MIDI.
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "debug_midi__arduino_serial.h"


// Implements blm_boards__comm_p2__leds__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p2__leds__debug_arduino_serial_midi__update_row(
        uint8_t matrix,
        uint8_t row,
        uint8_t color_code,
        uint8_t pattern)
{
}

void blm_boards__comm_p2__leds__debug_arduino_serial_midi__update_column(
        uint8_t matrix,
        uint8_t column,
        uint8_t color_code,
        uint8_t pattern)
{
}
