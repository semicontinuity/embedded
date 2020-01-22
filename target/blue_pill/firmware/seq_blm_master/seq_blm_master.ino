#include <Arduino.h>
//#include "build_number_defines.h"
#include <string.h>
//#include "midiXparser.h"
//#include "seq_blm_master.h"

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "midi_package.h"
#include "midi_sender_arduino.h"
#include "serial_midi_receiver_pt.h"
#include "sysex_handler_blm.h"
#include "sysex_handler_blm_arduino.h"

uint8_t led_state2 = 0;
uint8_t led_state = 0;


void midi_parser__on_channel_msg(midi_package_t midi_package) {
    digitalWrite(PA1, led_state = ~led_state);
    midi__send_package(midi_package);
}

void setup() {
    pinMode(PA5, OUTPUT);
    pinMode(PA1, OUTPUT);

    serial_midi_receiver__init();
}


void loop() {
    if (serial_midi_receiver__is_runnable()) {
        serial_midi_receiver__run();
    }
}
