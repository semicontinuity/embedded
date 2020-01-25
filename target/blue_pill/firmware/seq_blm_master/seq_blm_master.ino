#define BLM_SCALAR_NUM_COLOURS 2
#include <Arduino.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "blm_boards_leds__state.h"
#include "blm_boards_leds__state_updater.h"
#include "blm_boards_leds__state_scanner.h"

#ifdef DEBUG
#  include "blm_boards_leds__comm__debug_arduino_serial_midi.h"
#else
#  include "blm_boards_leds__comm__arduino_i2c.h"
#endif
#include "midi_package.h"
#include "midi_parser__pt.h"
#include "midi_sender__serial_arduino.h"
#include "midi_handler_blm.h"
#include "midi_receiver__serial_arduino_pt.h"
#include "blm_master__sysex_handler.h"
#include "blm_master__sysex_handler__arduino_serial_midi.h"


void setup() {
    pinMode(PA5, OUTPUT);
    pinMode(PA1, OUTPUT);

    Serial2.begin(31250);

    debug__serial__init(&Serial2);
    serial_midi_receiver__init(&Serial2);
#ifdef DEBUG
    blm_boards_leds__comm__init(&Serial2);
#endif
    blm_master__sysex_handler__init(&Serial2);
    midi_parser__init();

    blm_boards_leds__state__init();
}


void loop() {
    serial_midi_receiver__run();
    blm_boards_leds__state_scanner__run();
}
