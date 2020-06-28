// Debug translation of packed LED update commands from host
// to PACKED4 I2C commands to be sent to BLM.
// Encode these commands to MIDI messages and send them back to host.
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "debug_midi__arduino_serial.h"


// Implements blm_boards__comm__leds__p4_commands__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm__leds__p4_commands__debug_arduino_serial_midi__emit_packed4_command(uint8_t matrix, uint8_t command) {
    if (command & 0x80U) {
        debug_midi__channel_pressure(matrix, command & 0x7FU);
    } else {
        debug_midi__program_change(matrix, command);
    }
}
