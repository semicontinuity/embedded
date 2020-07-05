#include <Arduino.h>
#include <USBComposite.h>
#include <MinSysex.h>

#include "config.h"

USBCompositeSerial usbSerial;

#include "blm_boards__comm__events__reader.h"
#include "blm_boards__comm__events__reader__arduino_i2c.h"
#include "blm_boards__comm__events__handler.h"
#include "blm_boards__comm__events__handler__midi.h"

#include "midi_package.h"
#include "midi_sender__arduino_usb_midi.h"


class UsbMidi : public USBMIDI {
    void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) override {
    }
    void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) override {
    }
    // MIDI message A0 nn vv
    void handleVelocityChange(unsigned int channel, unsigned int note, unsigned int velocity) override {
    }
    // MIDI message B0 cc vv
    void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) override {
    }
    // MIDI message C0 pp
    void handleProgramChange(unsigned int channel, unsigned int program) override {
        usbSerial.println("CC");
        uint8_t event = blm_boards__comm_events__reader__read(0);
        usbSerial.println(event);
        if (event & 0x80U) {
            bool is_pressed = !(event & 0x01U);
            uint8_t button = (event & 0x7FU) >> 1U;
            blm_boards__comm_events__handler__on_button_event(0, button, is_pressed);
        }
    }
    void handleSysExData(unsigned char b) override {
    }
    void handleSysExEnd(unsigned char b) override {
    }
};

UsbMidi usbMidi;



// Implementation of callbacks for blm_boards__comm__events__reader.h
// -----------------------------------------------------------------------------

uint8_t blm_boards__comm_events__reader__read(uint8_t board) {
    return blm_boards__comm__events__arduino_i2c__read(board);
}

void blm_boards__comm_events__handler__on_button_event(uint8_t board, uint8_t button, bool is_pressed) {
    blm_boards__comm_events__handler__midi__on_button_event(board, button, is_pressed);
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void setup() {
    pinMode(PIN_LED_DEBUG, OUTPUT);

    pinMode(PIN_LED_HOST_CONNECTED, OUTPUT);
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);

    midi_sender__arduino_usb_midi__init(&usbMidi);

    TwoWire *wire = &WIRE;
    wire->begin();

    blm_boards__comm__events__arduino_i2c__init(wire, BLM_BOARDS_BASE_ADDRESS);
//    blm_boards__comm_events__reader__init();

    USBComposite.setProductId(0x0030);
    usbMidi.registerComponent();
    usbSerial.registerComponent();
    USBComposite.begin();
}


void loop() {
    usbMidi.poll();
//    blm_boards__comm_events__reader__run();
}

#pragma clang diagnostic pop
