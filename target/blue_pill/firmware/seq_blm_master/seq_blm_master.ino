#define BLM_SCALAR_NUM_COLOURS 2
#include <Arduino.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////

#include "multi_blm_leds_buffer.h"
#include "multi_blm_leds_buffer__blm_master_led_updates.h"
#include "multi_blm_leds_buffer__scanner.h"

#ifdef DEBUG
#  include "blm_boards_leds__comm__debug_arduino_serial_midi.h"
#else
#  include "blm_boards__comm__arduino_i2c.h"
#endif
#include "blm_master__channel_msg_handler.h"
#include "blm_master__sysex_msg_handler.h"
#include "blm_master__sysex_msg_handler__arduino_serial_midi.h"
#include "midi_receiver__serial_arduino_pt.h"
#include "midi_package.h"
#include "midi_parser__pt.h"
#include "midi_sender__serial_arduino.h"


// Implementation of callbacks from midi_parser_callbacks__channel_msg
// -----------------------------------------------------------------------------

void midi_parser__on_channel_msg(midi_package_t midi_package) {
    blm_master__channel_msg_handler__process(midi_package);
}


// Implements blm_boards_leds__state_scanner_callbacks.h
// -----------------------------------------------------------------------------

void blm_boards_leds__state_scanner__scan__update_one(uint8_t board, uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    blm_boards__comm__leds__update_one(board, led, r, g, b);
}

// Implements blm_master__leds.h
// -----------------------------------------------------------------------------

void leds__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    multi_blm_leds_buffer__blm_master__update_one(row, column, color_code);
}

void leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color) {
    multi_blm_leds_buffer__blm_master__update_row(row, is_second_half, pattern, color);
}

void leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color) {
    multi_blm_leds_buffer__blm_master__update_column(column, is_second_half, pattern, color);
}

void leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
    multi_blm_leds_buffer__blm_master__update_extra_row(is_second_half, pattern, color);
}

void leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
    multi_blm_leds_buffer__blm_master__update_extra_column(is_second_half, pattern, color);
}

void leds__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
    multi_blm_leds_buffer__blm_master__update_extra(is_second_half, pattern, color);
}


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
