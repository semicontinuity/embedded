#include <Arduino.h>
#include "midi_sender.h"


static HardwareSerial *midi_sender__serial;

void midi_sender__serial__init(HardwareSerial *serial) {
    midi_sender__serial = serial;
}

// no running status optimisation
// only channel messages
// no locking: use from the loop thread only
void midi_sender__send_package(midi_package_t p) {
    midi_sender__serial->write(p.evnt0);
    midi_sender__serial->write(p.evnt1);
    if ((p.evnt0 & 0xE0U) != 0xC0U) {
        midi_sender__serial->write(p.evnt2);
    }
}
