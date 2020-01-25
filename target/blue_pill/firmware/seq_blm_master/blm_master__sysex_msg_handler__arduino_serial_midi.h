#include <Arduino.h>
#include <stdint.h>
#include "blm_master__sysex_msg_handler__callbacks.h"

// Implementations of blm_master__sysex_msg_handler__callbacks.h
// -----------------------------------------------------------------------------

static const unsigned char blm_master__sysex_handler__header[5] = {0xf0, 0x00, 0x00, 0x7e, 0x4e };

static HardwareSerial *blm_master__sysex_handler__serial;

void blm_master__sysex_handler__init(HardwareSerial *serial) {
    blm_master__sysex_handler__serial = serial;
}


void blm_master__sysex_handler__handle_ping() {
    // will not block if amount of data is small: data are placed to transmit buffer
    blm_master__sysex_handler__serial->write(blm_master__sysex_handler__header, sizeof(blm_master__sysex_handler__header));
    blm_master__sysex_handler__serial->write(0x00);    // device ID
    blm_master__sysex_handler__serial->write(0x0f);    // ack_code
    blm_master__sysex_handler__serial->write(0x00);    // ack_arg
    blm_master__sysex_handler__serial->write(0xF7);    // footer
}

void blm_master__sysex_handler__handle_invalid_command() {
    // will not block if amount of data is small: data are placed to transmit buffer
    blm_master__sysex_handler__serial->write(blm_master__sysex_handler__header, sizeof(blm_master__sysex_handler__header));
    blm_master__sysex_handler__serial->write(0x00);    // device ID
    blm_master__sysex_handler__serial->write(0x0e);    // disack_code
    blm_master__sysex_handler__serial->write(0x0c);    // SYSEX_DISACK_INVALID_COMMAND
    blm_master__sysex_handler__serial->write(0xF7);    // footer
}

void blm_master__sysex_handler__handle_request_layout_info() {
    // will not block if amount of data is small: data are placed to transmit buffer
    blm_master__sysex_handler__serial->write(blm_master__sysex_handler__header, sizeof(blm_master__sysex_handler__header));
    blm_master__sysex_handler__serial->write(0x00);    // device ID
    blm_master__sysex_handler__serial->write(0x01);    // Command #1 (Layout Info)
    blm_master__sysex_handler__serial->write(0x10);    // Number of columns
    blm_master__sysex_handler__serial->write(0x04);    // Number of rows
    blm_master__sysex_handler__serial->write(0x02);    // number of LED colours
    blm_master__sysex_handler__serial->write(0x00);    // number of extra rows
    blm_master__sysex_handler__serial->write(0x00);    // number of extra columns
    blm_master__sysex_handler__serial->write(0x00);    // number of extra buttons (e.g. shift)
    blm_master__sysex_handler__serial->write(0xF7);    // footer
}
