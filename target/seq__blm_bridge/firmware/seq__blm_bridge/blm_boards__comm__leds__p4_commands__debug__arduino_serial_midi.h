// Allows to debug translation of packed LED update commands from host
// to PACKED4 I2C commands to be sent to BLM.
// Encodes these commands to MIDI messages and send them back to host.
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "debug__midi_sysex.h"


void blm_boards__comm__leds__p4_commands__debug__arduino_serial_midi__emit_command(uint8_t matrix, uint8_t command) {
#if DEBUG_MIDI_CHANNEL_MSG
    if (command & 0x80U) {
        midi_sender__program_change(matrix, command & 0x7FU);
    } else {
        midi_sender__channel_pressure(matrix, command);
    }
#endif
}
