#ifndef __MIDI_SENDER
#define __MIDI_SENDER

#include "midi_package.h"
#include "midi_sender__arduino_usb_midi.h"


void midi_sender__send_package(midi_package_t p) {
    midi_sender__arduino_usb_midi__send_package(p);
}

void midi_sender__program_change(uint8_t channel, uint8_t value) {
    midi_package_t p = {.ALL = 0};
    p.event = ProgramChange;
    p.chn = channel;
    p.value1 = value;
    midi_sender__send_package(p);
}

void midi_sender__channel_pressure(uint8_t channel, uint8_t value) {
    midi_package_t p = {.ALL = 0};
    p.event = Aftertouch;
    p.chn = channel;
    p.value1 = value;
    midi_sender__send_package(p);
}


void midi_sender__send_sysex_payload(uint8_t *payload, uint32 length) {
    midi_sender__arduino_usb_midi__send_sysex_payload(payload, length);
}


#endif
