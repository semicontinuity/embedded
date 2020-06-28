#include <Arduino.h>
#include "seq_blm_master__config.h"

//#include "blm_boards__comm_p1__leds__buffer.h"
//#include "blm_boards__comm_p1__leds__buffer__blm_master_updates.h"
//#include "blm_boards__comm_p1__leds__buffer__scanner.h"
//#include "blm_boards__comm_p1__leds__debug_arduino_serial_midi.h"
//#include "blm_boards__comm_p1__leds__arduino_i2c.h"

#include "blm_boards__comm__leds__commands__buffer.h"
#include "blm_boards__comm__leds__commands__buffer__blm_master_updates.h"
#include "blm_boards__comm__leds__commands__buffer__scanner.h"
#include "blm_boards__comm__leds__commands__debug_arduino_serial_midi.h"
#include "blm_boards__comm__leds__commands__arduino_i2c.h"
#include "blm_boards__comm__leds__palette_uploader.h"

#include "blm_boards__comm__events__reader.h"
#include "blm_boards__comm__events__reader__arduino_i2c.h"
#include "blm_boards__comm__events__handler.h"
#include "blm_boards__comm__events__handler__midi.h"

#include "blm_master__channel_msg_handler.h"
#include "blm_master__sysex_msg_handler__callbacks.h"
#include "blm_master__sysex_msg_handler__sender.h"
#include "blm_master__sysex_msg_handler__set_palette_data.h"
#include "blm_master__sysex_msg_handler.h"
#include "blm_master__alive_handler.h"

#include "midi_package.h"
#include "midi_receiver__serial_arduino_pt.h"
#include "midi_parser__pt.h"
#include "midi_sender__serial_arduino.h"


// Implementation of callbacks for blm_boards__comm__events__reader_pt.h
// -----------------------------------------------------------------------------

uint8_t blm_boards__comm_events__reader__read(uint8_t board) {
    return blm_boards__comm__events__arduino_i2c__read(board);
}

// Implementation of callbacks for blm_boards__comm__events__handler.h
// -----------------------------------------------------------------------------

void blm_boards__comm_events__handler__on_button_event(uint8_t board, uint8_t button, bool is_pressed) {
    if (blm_master__alive_handler__is_host_connected()) {
        blm_boards__comm_events__handler__midi__on_button_event(board, button, is_pressed);
    }
}

// Implementation of callbacks from midi_parser_callbacks__channel_msg
// -----------------------------------------------------------------------------

void midi_parser__on_channel_msg(midi_package_t midi_package) {
    blm_master__channel_msg_handler__process(midi_package);
    blm_master__alive_handler__midi_channel_msg_received();
}


// Implements blm_boards__comm_p1__leds__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

/*
void blm_boards__comm_p1__leds__buffer__scanner__update_one(uint8_t matrix, uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    if (DEBUG_COMM_LEDS) {
        blm_boards__comm_p1__leds__debug_arduino_serial_midi__update_one(matrix, led, r, g);
    } else {
        blm_boards__comm_p1__leds__arduino_i2c__update_one(matrix, led, r, g, b);
    }
}
*/

// Implements blm_boards__comm__leds__commands__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm__leds__commands__buffer__scanner__emit_packed4_command(uint8_t matrix, uint8_t command) {
    if (DEBUG_COMM_LEDS) {
        blm_boards__comm__leds__commands__debug_arduino_serial_midi__emit_packed4_command(matrix, command);
    } else {
        blm_boards__comm__leds__commands__arduino_i2c__emit_packed4_command(matrix, command);
    }
}


// Implements blm_master__leds.h
// -----------------------------------------------------------------------------

void blm_master__leds__select_palette(uint8_t palette) {
    blm_boards__comm__leds__palette_uploader__request(palette);
}

void blm_master__leds__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_one(row, column, color_code);
}

void blm_master__leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_row(row, is_second_half, pattern, color_code);
}

void blm_master__leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_column(column, is_second_half, pattern, color_code);
}

void blm_master__leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_extra_row(is_second_half, pattern, color_code);
}

void blm_master__leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_extra_column(is_second_half, pattern, color_code);
}

void blm_master__leds__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    blm_boards__comm__leds__commands__buffer__blm_master__update_extra(is_second_half, pattern, color_code);
}

// Implements blm_master__sysex_msg_handler__callbacks.h
// -----------------------------------------------------------------------------

void blm_master__sysex_msg_handler__handle_ping() {
    blm_master__sysex_msg_sender__send_ack();
}

void blm_master__sysex_msg_handler__handle_invalid_command() {
    blm_master__sysex_msg_sender__send_disack_invalid_command();
}

void blm_master__sysex_msg_handler__handle_request_layout_info() {
    blm_master__sysex_msg_sender__send_layout_info();
}


void setup() {
    pinMode(PIN_LED_DEBUG, OUTPUT);
    pinMode(PIN_LED_HOST_CONNECTED, OUTPUT);


    HardwareSerial *serial = &SERIAL_PORT;
    serial->begin(SERIAL_BAUD_RATE);
    debug_midi__serial__init(serial);
    midi_receiver__serial__init(serial);
    midi_sender__serial__init(serial);
    blm_master__sysex_msg_sender__init(serial);

    TwoWire *wire = &WIRE;
    wire->begin();

    if (!DEBUG_COMM_LEDS) {
//        blm_boards__comm_p1__leds__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
        blm_boards__comm__leds__commands__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
        blm_boards__comm__leds__palette_uploader__init(wire, BLM_BOARDS_BASE_ADDRESS);
    }

    if (!DEBUG_COMM_EVENTS) {
        blm_boards__comm__events__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
    }


    midi_parser__init();
    blm_boards__comm_events__reader__init();

    blm_boards__comm__leds__commands__buffer__init();
}


void loop() {
    if (midi_receiver__serial__is_runnable()) {
        midi_receiver__serial__run();
    } else {
        // prefer handling of incoming MIDI messages
        blm_master__alive_handler__run();
    }


    if (blm_boards__comm__leds__commands__buffer__scanner__is_runnable()) {
        blm_boards__comm__leds__commands__buffer__scanner__run();
    } else {
        // if there are events to be sent to BLM boards, prefer to send them first
        // to avoid any visual lags

        if (!DEBUG_COMM_EVENTS) {
            blm_boards__comm_events__reader__run();
        }
    }

    if (blm_boards__comm__leds__palette_uploader__is_runnable()) {
        blm_boards__comm__leds__palette_uploader__run();
    }
}
