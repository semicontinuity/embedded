#ifndef __MIDI_SENDER
#define __MIDI_SENDER

#include "midi_package.h"
#include "midi_sender__arduino_serial.h"


// For serial:
// - no running status optimisation
// - only channel messages
// - no locking: use from the loop thread only
void midi_sender__send_package(midi_package_t p) {
    midi_sender__arduino_serial__send_package(p);
}

void midi_sender__send_poly_pressure(uint8_t channel, uint8_t value1, uint8_t value2) {
    midi_package_t p = {.ALL = 0};
    p.event = PolyPressure;
    p.chn = channel;
    p.value1 = value1;
    p.value2 = value2;
    midi_sender__send_package(p);
}


void midi_sender__send_control_change(uint8_t channel, uint8_t value1, uint8_t value2) {
    midi_package_t p = {.ALL = 0};
    p.event = CC;
    p.chn = channel;
    p.value1 = value1;
    p.value2 = value2;
    midi_sender__send_package(p);
}


void midi_sender__send_sysex_payload(uint8_t *payload, uint32_t length) {
    midi_sender__arduino_serial__send_sysex_payload(payload, length);
}

#endif
