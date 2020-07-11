#include <Arduino.h>
#include <USBComposite.h>

#include "test_forwarding_midi__config.h"

USBCompositeSerial usbSerial;

#include "host__sysex_msg_handler__callbacks.h"
#include "host__sysex_msg_sender.h"
#include "host__sysex_msg_handler.h"

#include "midi_package.h"
#include "midi_parser.h"
#include "midi_sender__arduino_usb_midi.h"

#include "arduino_serial__reader.h"
#include "midi_sender__arduino_serial.h"


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
    }
    void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) override {
    }
    // MIDI message A0 nn vv
    void handleVelocityChange(unsigned int channel, unsigned int note, unsigned int velocity) override {
        midi_sender__arduino_serial__send_package(fill_midi_package(PolyPressure, channel, note, velocity));
    }
    // MIDI message B0 cc vv
    void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) override {
    }
    // MIDI message C0 pp
    void handleProgramChange(unsigned int channel, unsigned int program) override {
    }
    void handleSysExData(unsigned char b) override {
        host__sysex_msg_handler__on_sysex_data(b);
    }
    void handleSysExEnd(void) override {
        host__sysex_msg_handler__on_sysex_finish();
    }
};

UsbMidi usbMidi;


// Implementation of callbacks for midi__bridge_helper__parser
// -----------------------------------------------------------------------------

void host__on_channel_msg(midi_package_t midi_package) {
    usbSerial.println("host__on_channel_msg");
    midi_sender__send_package(midi_package);
}


// Implementation of host__sysex_msg_handler__callbacks.h
// -----------------------------------------------------------------------------

void host__sysex_msg_handler__handle_ping() {
    usbSerial.println("ping");
    host__sysex_msg_sender__send_ack();
}

void host__sysex_msg_handler__handle_invalid_command() {
    usbSerial.println("invalid_command");
    host__sysex_msg_sender__send_disack_invalid_command();
}

void host__sysex_msg_handler__handle_request_layout_info() {
    usbSerial.println("request_layout_info");
    host__sysex_msg_sender__send_layout_info();
}

void host__sysex_msg_handler__handle_set_palette_data(uint8_t palette, uint8_t *data, int32_t length) {
}


struct midi_parser midi__bridge_helper__parser = {
        .on_channel_msg     = host__on_channel_msg,
        .on_sysex_data      = host__sysex_msg_handler__on_sysex_data,
        .on_sysex_finish    = host__sysex_msg_handler__on_sysex_finish,
        .thread             = {.lc = nullptr},
        .cable              = 0
};

static struct arduino_serial__reader midi__bridge_helper__reader {
        .arduino_serial     = &BRIDGE_HELPER_SERIAL_PORT,
        .process            = [](uint8_t b) { return midi_parser__process(&midi__bridge_helper__parser, b); }
};


void setup() {
    pinMode(PIN_LED_DEBUG, OUTPUT);

    pinMode(PIN_LED_HOST_CONNECTED, OUTPUT);
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);

    midi_sender__arduino_usb_midi__init(&usbMidi);

    HardwareSerial *serial = &BRIDGE_HELPER_SERIAL_PORT;
    serial->begin(BRIDGE_HELPER_SERIAL_BAUD_RATE);

    midi_sender__arduino_serial__init(&BRIDGE_HELPER_SERIAL_PORT);

    USBComposite.setProductId(0x0030);
    usbMidi.registerComponent();
    usbSerial.registerComponent();
    USBComposite.begin();
}


void loop() {
    usbMidi.poll();
    if (arduino_serial__reader__is_runnable(&midi__bridge_helper__reader)) {
        arduino_serial__reader__run(&midi__bridge_helper__reader);
    }
}
