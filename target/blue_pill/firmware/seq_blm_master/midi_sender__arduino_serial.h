#ifndef __MIDI_SENDER__ARDUINO_SERIAL
#define __MIDI_SENDER__ARDUINO_SERIAL

#include <Arduino.h>
#include "midi_package.h"


static HardwareSerial *midi_sender__arduino_usb_midi;

void midi_sender__arduino_serial__init(HardwareSerial *serial) {
    midi_sender__arduino_usb_midi = serial;
}

// no running status optimisation
// only channel messages
// no locking: use from the loop thread only
void midi_sender__arduino_serial__send_package(midi_package_t p) {
    midi_sender__arduino_usb_midi->write(p.evnt0);
    midi_sender__arduino_usb_midi->write(p.evnt1);
    if ((p.evnt0 & 0xE0U) != 0xC0U) {
        midi_sender__arduino_usb_midi->write(p.evnt2);
    }
}


#endif
