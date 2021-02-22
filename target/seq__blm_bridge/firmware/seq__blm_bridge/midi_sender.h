#ifndef __MIDI_SENDER
#define __MIDI_SENDER

#include "midi_package.h"
#include "midi_sender__arduino_serial.h"
#include "midi_sender__arduino_usb_midi.h"
#include "midi_port.h"


// For serial:
// - no running status optimisation
// - only channel messages
// - no locking: use from the loop thread only
void midi_sender__send_package(midi_port_t port, midi_package_t p) {
    if (port == MIDI_PORT_SERIAL_1 || port == MIDI_PORT_UNDEFINED) {
        midi_sender__arduino_serial__send_package(p);
    }
    if (port == MIDI_PORT_USB || port == MIDI_PORT_UNDEFINED) {
        midi_sender__arduino_usb_midi__send_package(p);
    }
}

void midi_sender__program_change(midi_port_t port, uint8_t channel, uint8_t value) {
    midi_package_t p = {.ALL = 0};
    p.event = ProgramChange;
    p.chn = channel;
    p.value1 = value;
    midi_sender__send_package(port, p);
}

void midi_sender__channel_pressure(midi_port_t port, uint8_t channel, uint8_t value) {
    midi_package_t p = {.ALL = 0};
    p.event = Aftertouch;
    p.chn = channel;
    p.value1 = value;
    midi_sender__send_package(port, p);
}


void midi_sender__send_sysex_message(midi_port_t port, uint8_t *payload, uint32 length) {
    if (port == MIDI_PORT_SERIAL_1 || port == MIDI_PORT_UNDEFINED) {
        midi_sender__arduino_serial__send_sysex_message(payload, length);
    }
    if (port == MIDI_PORT_USB || port == MIDI_PORT_UNDEFINED) {
        midi_sender__arduino_usb_midi__send_sysex_message(payload, length);
    }
}


#endif
