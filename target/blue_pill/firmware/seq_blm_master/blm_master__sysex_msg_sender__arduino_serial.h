#ifndef __BLM_MASTER__SYSEX_MSG_SENDER__ARDUINO_SERIAL
#define __BLM_MASTER__SYSEX_MSG_SENDER__ARDUINO_SERIAL

#include <Arduino.h>


static HardwareSerial *blm_master__sysex_msg_sender__arduino_serial;

void blm_master__sysex_msg_sender__arduino_serial__init(HardwareSerial *serial) {
    blm_master__sysex_msg_sender__arduino_serial = serial;
}

void blm_master__sysex_msg_sender__arduino_serial__send(uint8_t *payload, uint32 length) {
    for (uint8_t *p = payload; p < payload + length; p++) {
        blm_master__sysex_msg_sender__arduino_serial->write(*p);
    }
}

#endif