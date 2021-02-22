#include <Arduino.h>
#include <USBComposite.h>

#include "test_usb_serial__config.h"

USBCompositeSerial usbSerial;

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
    }
    void handleSysExData(unsigned char b) override {
    }
    void handleSysExEnd(void) override {
    }
};

UsbMidi usbMidi;


void setup() {
    pinMode(PIN_LED_HOST_CONNECTED, OUTPUT);
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);

    USBComposite.setProductId(0x0030);
    usbMidi.registerComponent();
    usbSerial.registerComponent();
    USBComposite.begin();
}


void loop() {
    usbMidi.poll();

    digitalWrite(PIN_LED_HOST_CONNECTED, usbMidi.isConnected() ? PIN_LED_HOST_CONNECTED_ON : PIN_LED_HOST_CONNECTED_OFF);

    delay(1000);

    usbMidi.sendProgramChange(0, 63);
}
