#define LC_INCLUDE "lc-addrlabels.h"
#include <Arduino.h>
#include <stdbool.h>
#include "midi_parser.h"

static HardwareSerial *serial_midi_receiver__serial;

void serial_midi_receiver__init(HardwareSerial *serial) {
    serial_midi_receiver__serial = serial;
}

bool serial_midi_receiver__is_runnable() {
    return serial_midi_receiver__serial->available();
}

void serial_midi_receiver__run() {
    if (serial_midi_receiver__is_runnable()) {
        midi_parser__run(serial_midi_receiver__serial->read());
    }
}
