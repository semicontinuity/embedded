#define BLM_SCALAR_NUM_COLOURS 2
#include <Arduino.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "blm_boards_leds__state.h"
#include "blm_boards_leds__state_updater.h"
#include "blm_boards_leds__state_scanner.h"
//#include "blm_boards_leds__i2c_arduino.h"
#include "blm_boards_leds__comm__debug_arduino_serial_midi.h"
#include "midi_package.h"
#include "midi_parser__pt.h"
#include "midi_sender_arduino.h"
#include "midi_handler_blm.h"
#include "serial_midi_receiver_pt.h"
#include "blm_master__sysex_handler.h"
#include "blm_master__sysex_handler__arduino_serial_midi.h"


void setup() {
    pinMode(PA5, OUTPUT);
    pinMode(PA1, OUTPUT);
    blm_boards_leds__comm__init(&Serial2);
    blm_boards_leds__init();
    midi_parser__init();
    serial_midi_receiver__init();
}


void loop() {
    serial_midi_receiver__run();
    blm_boards_leds__state_scanner__run();
}
