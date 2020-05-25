#include <Arduino.h>
#include <Wire.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "bridge__sysex_msg_handler.h"

#include "midi_receiver__serial_arduino_pt.h"
#include "midi_package.h"
#include "midi_parser__pt.h"


// Implementation of callbacks from midi_parser_callbacks__channel_msg
// -----------------------------------------------------------------------------

void midi_parser__on_channel_msg(midi_package_t midi_package) {
}


TwoWire Wire2(2);


void setup() {
    pinMode(PA5, OUTPUT);
    pinMode(PA1, OUTPUT);

    TwoWire *wire = &Wire2;
    wire->begin();
    bridge__sysex_handler__init(wire);

    HardwareSerial *serial = &Serial2;
    serial->begin(31250);
    serial_midi_receiver__init(serial);

    midi_parser__init();
}


void loop() {
    if (serial_midi_receiver__is_runnable()) {
        serial_midi_receiver__run();
    }
}
