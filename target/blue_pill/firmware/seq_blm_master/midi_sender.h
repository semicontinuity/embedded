#ifndef __MIDI_SENDER
#define __MIDI_SENDER

#include "midi_package.h"
#include "midi_sender__arduino_serial.h"
#include "midi_sender__arduino_usb_midi.h"

// For serial:
// - no running status optimisation
// - only channel messages
// - no locking: use from the loop thread only
void midi_sender__send_package(midi_package_t p) {
    midi_sender__arduino_serial__send_package(p);
    midi_sender__arduino_usb_midi__send_package(p);
}

void midi_sender__send_sysex(uint8_t *payload, uint32 length) {
    midi_sender__arduino_serial__send_sysex(payload, length);
    midi_sender__arduino_usb_midi__send_sysex(payload, length);
}


#endif
