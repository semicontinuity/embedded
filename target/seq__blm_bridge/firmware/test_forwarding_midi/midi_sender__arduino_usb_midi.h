#ifndef __MIDI_SENDER__ARDUINO_USB_MIDI
#define __MIDI_SENDER__ARDUINO_USB_MIDI

#include <USBComposite.h>
#include "midi_package.h"


static USBMIDI *midi_sender__arduino_usb_midi;

void midi_sender__arduino_usb_midi__init(USBMIDI *port) {
    midi_sender__arduino_usb_midi = port;
}

void midi_sender__arduino_usb_midi__send_package(midi_package_t p) {
    midi_sender__arduino_usb_midi->writePacket(p.ALL);
}

void midi_sender__arduino_usb_midi__send_sysex_payload(uint8_t *payload, uint32 length) {
    midi_sender__arduino_usb_midi->sendSysexPayload(payload, length);
}

#endif
