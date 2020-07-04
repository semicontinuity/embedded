#ifndef __BLM_MASTER__SYSEX_MSG_SENDER__USB_MIDI
#define __BLM_MASTER__SYSEX_MSG_SENDER__USB_MIDI

#include <USBComposite.h>

static USBMIDI *blm_master__sysex_msg_sender__usb_midi;

void blm_master__sysex_msg_sender__usb_midi__init(USBMIDI *usbmidi) {
    blm_master__sysex_msg_sender__usb_midi = usbmidi;
}

void blm_master__sysex_msg_sender__usb_midi__send(uint8_t *payload, uint32 length) {
    blm_master__sysex_msg_sender__usb_midi->sendSysexPacket(payload, length);
}

#endif