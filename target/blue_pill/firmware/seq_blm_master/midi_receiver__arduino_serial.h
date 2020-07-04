#include <Arduino.h>
#include <stdbool.h>
#include "midi_parser.h"

static HardwareSerial *midi_receiver__arduino_serial;

void midi_receiver__arduino_serial__init(HardwareSerial *serial) {
    midi_receiver__arduino_serial = serial;
}

bool midi_receiver__arduino_serial__is_runnable() {
    return midi_receiver__arduino_serial->available();
}

void midi_receiver__arduino_serial__run() {
    midi_parser__process(midi_receiver__arduino_serial->read());
}
