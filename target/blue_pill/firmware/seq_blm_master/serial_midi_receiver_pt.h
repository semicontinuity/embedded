#define LC_INCLUDE "lc-addrlabels.h"
#include <Arduino.h>
#include <stdbool.h>
#include "midi_parser.h"


void serial_midi_receiver__init() {
    Serial2.begin(31250);
}

bool serial_midi_receiver__is_runnable() {
    return Serial2.available();
}

void serial_midi_receiver__run() {
    if (serial_midi_receiver__is_runnable()) {
        midi_parser__run(Serial2.read());
    }
}
