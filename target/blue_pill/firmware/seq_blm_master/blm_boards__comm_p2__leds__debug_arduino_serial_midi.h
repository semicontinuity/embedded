// Debugs LED update commands by sending them over serial port as MIDI.
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "debug_midi__arduino_serial.h"


// Implements blm_boards__comm_p2__leds__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p2__leds__debug_arduino_serial_midi__emit_command(
        uint8_t matrix,
        uint8_t command)
{
    if (command & 0x80U) {
        debug_midi__channel_pressure(matrix, command & 0x7FU);
    } else {
        debug_midi__program_change(matrix, command);
    }
}