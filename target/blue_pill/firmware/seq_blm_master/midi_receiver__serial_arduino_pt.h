#include <Arduino.h>
#include <stdbool.h>
#include "midi_parser.h"

static HardwareSerial *midi_receiver__serial;

void midi_receiver__serial__init(HardwareSerial *serial) {
    midi_receiver__serial = serial;
}

bool midi_receiver__serial__is_runnable() {
    return midi_receiver__serial->available();
}

void midi_receiver__serial__run() {
    midi_parser__process(midi_receiver__serial->read());
}
