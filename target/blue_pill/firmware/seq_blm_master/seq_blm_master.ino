#include <Arduino.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "midi_package.h"
#include "midi_parser__pt.h"
#include "midi_sender_arduino.h"
#include "midi_handler_blm.h"
#include "serial_midi_receiver_pt.h"
#include "sysex_handler_blm.h"
#include "sysex_handler_blm_arduino.h"
#include "blm_boards_comm_i2c_arduino.h"


void setup() {
    pinMode(PA5, OUTPUT);
    pinMode(PA1, OUTPUT);
    blm_boards_comm__init();
    midi_parser__init();
    serial_midi_receiver__init();
}


void loop() {
    serial_midi_receiver__run();
}
