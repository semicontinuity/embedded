#ifndef __MIDI_SENDER
#define __MIDI_SENDER

#include <Arduino.h>
#include "midi_sender__arduino_serial.h"
#include "midi_package.h"

// no running status optimisation
// only channel messages
// no locking: use from the loop thread only
void midi_sender__send_package(midi_package_t p) {
    midi_sender__arduino_serial__send_package(p);
}


#endif
