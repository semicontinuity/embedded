#include <Arduino.h>
#include <USBComposite.h>

#include "seq__blm_bridge__config.h"

USBCompositeSerial usbSerial;

#include "blm_boards__comm__leds__p4_commands__buffer.h"
#include "blm_boards__comm__leds__p4_commands__buffer__scanner.h"
#include "blm_boards__comm__leds__p4_commands__arduino_i2c.h"
#include "blm_boards__comm__leds__p4_commands__debug__arduino_serial_midi.h"

#include "blm_boards__comm__leds__u128_commands__buffer.h"
#include "blm_boards__comm__leds__u128_commands__buffer__scanner.h"
#include "blm_boards__comm__leds__u128_commands__arduino_i2c.h"

#include "blm_boards__comm__leds__palette__buffer.h"
#include "blm_boards__comm__leds__palette__uploader.h"

#include "blm_boards__comm__events__reader.h"
#include "blm_boards__comm__events__reader__arduino_i2c.h"
#include "blm_boards__comm__events__handler.h"
#include "blm_boards__comm__events__handler__midi.h"
#include "blm_boards__comm__events__handler__test_mode.h"

#include "host__channel_msg_handler.h"
#include "host__sysex_msg_handler__callbacks.h"
#include "host__sysex_msg_sender.h"
#include "host__sysex_msg_handler.h"
#include "host__alive_handler.h"
#include "host__leds_msg_handler.h"

#include "midi_port.h"
#include "midi_package.h"
#include "midi_parser.h"
#include "midi_sender__arduino_serial.h"
#include "midi_sender__arduino_usb_midi.h"
#include "arduino_serial__reader.h"


static midi_package_t fill_midi_package(unsigned int event, unsigned int channel, unsigned int note, unsigned int velocity) {
    midi_package_t p;
    p.event = event,
    p.chn = static_cast<uint8_t>(channel),
    p.note = static_cast<uint8_t>(note),
    p.velocity = static_cast<uint8_t>(velocity);
    return p;
}

class UsbMidi : public USBMIDI {
    void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) override {
        host__channel_msg_handler__process_single_led_change_event(fill_midi_package(NoteOff, channel, note, velocity));
        host__alive_handler__host_connected__set(MIDI_PORT_USB);
    }
    void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) override {
        host__channel_msg_handler__process_single_led_change_event(fill_midi_package(NoteOn, channel, note, velocity));
        host__alive_handler__host_connected__set(MIDI_PORT_USB);
    }
    // MIDI message A0 nn vv
    void handleVelocityChange(unsigned int channel, unsigned int note, unsigned int velocity) override {
        host__channel_msg_handler__process_single_led_color_event(fill_midi_package(PolyPressure, channel, note, velocity));
        host__alive_handler__host_connected__set(MIDI_PORT_USB);
    }
    // MIDI message B0 cc vv
    void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) override {
        host__channel_msg_handler__process_packed_leds_change_event(fill_midi_package(CC, channel, controller, value));
        host__alive_handler__host_connected__set(MIDI_PORT_USB);
    }
    // MIDI message C0 pp
    void handleProgramChange(unsigned int channel, unsigned int program) override {
        host__leds_msg__select_palette(program & 0x0Fu);
        host__alive_handler__host_connected__set(MIDI_PORT_USB);
    }
    void handleSysExData(unsigned char b) override {
        host__sysex_msg_handler__on_sysex_data(b);
    }
    void handleSysExEnd(void) override {
        host__sysex_msg_handler__on_sysex_finish();
    }
};

UsbMidi usbMidi;

// Implementation of callbacks for blm_boards__comm__events__reader.h
// -----------------------------------------------------------------------------

uint8_t blm_boards__comm_events__reader__read(uint8_t board) {
    return blm_boards__comm__events__arduino_i2c__read(board);
}

// Implementation of callbacks for blm_boards__comm__events__handler.h
// -----------------------------------------------------------------------------

void blm_boards__comm_events__handler__on_button_event(uint8_t board, uint8_t button, bool is_pressed) {
    midi_port_t port = host__alive_handler__host_connected__get();
    if (port != MIDI_PORT_UNDEFINED) {
        midi_sender__send_package(port, blm_boards__comm_events__handler__midi__package(board, button, is_pressed));
    } else {
        blm_boards__comm_events__handler__test_mode__on_button_event(board, button, is_pressed);
    }
}

// Implementation of callbacks from midi_parser__callbacks__channel_msg.h
// -----------------------------------------------------------------------------

void host__on_channel_msg(midi_package_t midi_package) {
    host__channel_msg_handler__process(midi_package);
    host__alive_handler__host_connected__set(MIDI_PORT_SERIAL_1);
}


// Implements blm_boards__comm__leds__p4_commands__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm__leds__p4_commands__buffer__scanner__emit_command(uint8_t matrix, uint8_t command) {
    if (DEBUG_COMM_LEDS) {
        blm_boards__comm__leds__p4_commands__debug__arduino_serial_midi__emit_command(matrix, command);
    } else {
        blm_boards__comm__leds__p4_commands__arduino_i2c__emit_command(matrix, command);
    }
}

// Implements blm_boards__comm__leds__u128_commands__buffer__scanner__callbacks.h
// -----------------------------------------------------------------------------

void blm_boards__comm__leds__u128_commands__buffer__scanner__emit_command(uint8_t matrix, uint8_t led, uint8_t color) {
    blm_boards__comm__leds__u128_commands__arduino_i2c__emit_command(matrix, led, color);
}


// Implements host__leds_msg.h
// -----------------------------------------------------------------------------

void host__leds_msg__select_palette(uint8_t palette) {
    blm_boards__comm__leds__palette__uploader__request(palette);
}

/**
 * @param color indexed color from the current palette, values: 0-127
 */
void host__leds_msg__update_color(uint8_t row, uint8_t column, uint8_t color) {
    host__leds_msg_handler__u128__update_color(row, column, color);
}

/**
 * @param color_code 00..1f: black; 20..3f: green; 40..5f red; 60..7f yellow
 */
void host__leds_msg__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    host__leds_msg_handler__u128__update_one(row, column, color_code);
}

void host__leds_msg__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    host__leds_msg_handler__p4__update_row(row, is_second_half, pattern, color_code);
}

void host__leds_msg__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    host__leds_msg_handler__p4__update_column(column, is_second_half, pattern, color_code);
}

void host__leds_msg__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    host__leds_msg_handler__p4__update_extra_row(is_second_half, pattern, color_code);
}

void host__leds_msg__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    host__leds_msg_handler__p4__update_extra_column(is_second_half, pattern, color_code);
}

void host__leds_msg__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    host__leds_msg_handler__p4__update_extra_leds(is_second_half, pattern, color_code);
}


void host__sysex_msg_handler__handle_ping() {
    host__sysex_msg_sender__send_ack(host__alive_handler__host_connected__get());   // hack
}

void host__sysex_msg_handler__handle_invalid_command() {
    host__sysex_msg_sender__send_disack_invalid_command(host__alive_handler__host_connected__get());    // hack
}


void populate_midibox_palette(int palette) {
    // format: GRB
    int offset = 0;
    for (int e = 0; e < 32; e++) {
        // black
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        // green
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 8;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        // red
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 8;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
        // yellow
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 8;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 8;
        blm_boards__comm__leds__palette__buffer__palettes[palette][offset++] = 0;
    }
}


void host__sysex_msg_handler__handle_request_layout_info() {
    host__sysex_msg_sender__send_layout_info(host__alive_handler__host_connected__get());   // hack
}

void host__sysex_msg_handler__handle_set_palette_data(uint8_t palette, uint8_t *data, int32_t length) {
    blm_boards__comm__leds__palette__buffer__palettes__set_palette_data(palette, data, length);
}


struct midi_parser midi__host__parser = {
        .on_channel_msg     = host__on_channel_msg,
        .on_sysex_data      = host__sysex_msg_handler__on_sysex_data,
        .on_sysex_finish    = host__sysex_msg_handler__on_sysex_finish,
        .thread             = {.lc = nullptr},
        .cable              = 0
};

struct midi_parser midi__pot__parser = {
        .on_channel_msg     = [](midi_package_t midi_package) { midi_sender__send_package(host__alive_handler__host_connected__get(), midi_package); },
        .on_sysex_data      = [](uint8_t b) {},
        .on_sysex_finish    = []() {},
        .thread             = {.lc = nullptr},
        .cable              = 0
};

static struct arduino_serial__reader midi__host__reader {
        .arduino_serial     = &HOST_SERIAL_PORT,
        .process            = [](uint8_t b) { return midi_parser__process(&midi__host__parser, b); }
};

static struct arduino_serial__reader midi__pot_1__reader {
        .arduino_serial     = &POT_READER_1_SERIAL_PORT,
        .process            = [](uint8_t b) { return midi_parser__process(&midi__pot__parser, b); }
};

static struct arduino_serial__reader midi__pot_2__reader {
        .arduino_serial     = &POT_READER_2_SERIAL_PORT,
        .process            = [](uint8_t b) { return midi_parser__process(&midi__pot__parser, b); }
};


void setup() {
    pinMode(PIN_LED_DEBUG, OUTPUT);

    pinMode(PIN_LED_HOST_CONNECTED, OUTPUT);
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);

    midi_sender__arduino_usb_midi__init(&usbMidi);

    POT_READER_1_SERIAL_PORT.begin(POT_READER_1_SERIAL_BAUD_RATE);
    POT_READER_2_SERIAL_PORT.begin(POT_READER_2_SERIAL_BAUD_RATE);

    HardwareSerial *serial = &HOST_SERIAL_PORT;
    serial->begin(HOST_SERIAL_BAUD_RATE);
    midi_sender__arduino_serial__init(serial);

    TwoWire *wire = &WIRE;
    wire->begin();

    if (!DEBUG_COMM_LEDS) {
        blm_boards__comm__leds__p4_commands__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
        blm_boards__comm__leds__u128_commands__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
        blm_boards__comm__leds__palette__uploader__init(wire, BLM_BOARDS_BASE_ADDRESS);
    }

    if (!DEBUG_COMM_EVENTS) {
        blm_boards__comm__events__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
    }

    blm_boards__comm_events__reader__init();
    blm_boards__comm__leds__p4_commands__buffer__init();
    blm_boards__comm__leds__u128_commands__buffer__init();
    blm_boards__comm_events__handler__test_mode__init();

    populate_midibox_palette(0);
//    host__leds_msg__select_palette(0);

    USBComposite.setProductId(0x0030);
    usbMidi.registerComponent();
    usbSerial.registerComponent();
    USBComposite.begin();
}

unsigned int counter;

void loop() {
    usbMidi.poll();

    if (arduino_serial__reader__is_runnable(&midi__host__reader)) {
        arduino_serial__reader__run(&midi__host__reader);
    }

    if (arduino_serial__reader__is_runnable(&midi__pot_1__reader)) {
        arduino_serial__reader__run(&midi__pot_1__reader);
    }

    if (arduino_serial__reader__is_runnable(&midi__pot_2__reader)) {
        arduino_serial__reader__run(&midi__pot_2__reader);
    }
/*
    if (host__alive_handler__is_runnable()) {
        host__alive_handler__run();
    }*/

    // if there are events to be sent to BLM boards, prefer to send them first
    // to avoid any visual lags
/*
    if (blm_boards__comm__leds__p4_commands__buffer__scanner__is_runnable()) {
        blm_boards__comm__leds__p4_commands__buffer__scanner__run();
    } else if (blm_boards__comm__leds__u128_commands__buffer__scanner__is_runnable()) {
        blm_boards__comm__leds__u128_commands__buffer__scanner__run();
    } else {
        if (!DEBUG_COMM_EVENTS) {
            ++counter;
            if ((counter & 0xFFFFU) == 0U) {
                blm_boards__comm_events__reader__run();
            }
        }
    }
*/

    // NB: Full Palette transfer takes ~40ms @ 100KHz per board, thus 640ms for 16 boards!
//    if (blm_boards__comm__leds__palette__uploader__is_runnable()) {
//        blm_boards__comm__leds__palette__uploader__run();
//    }
}
