#include <Arduino.h>
#include <stdint.h>
#include "sysex_handler_blm_callbacks.h"

// Implementations of callbacks, defined in sysex_handler_blm_callbacks.h
// -----------------------------------------------------------------------------

static const unsigned char sysex_blm__header[5] = { 0xf0, 0x00, 0x00, 0x7e, 0x4e };

void sysex_blm__handle_ping() {
    // will not block if amount of data is small: data are placed to transmit buffer
    Serial2.write(sysex_blm__header, sizeof(sysex_blm__header));
    Serial2.write(0x00);    // device ID
    Serial2.write(0x0f);    // ack_code
    Serial2.write(0x00);    // ack_arg
    Serial2.write(0xF7);    // footer
}

void sysex_blm__handle_invalid_command() {
    // will not block if amount of data is small: data are placed to transmit buffer
    Serial2.write(sysex_blm__header, sizeof(sysex_blm__header));
    Serial2.write(0x00);    // device ID
    Serial2.write(0x0e);    // disack_code
    Serial2.write(0x0c);    // SYSEX_DISACK_INVALID_COMMAND
    Serial2.write(0xF7);    // footer
}

void sysex_blm__handle_request_layout_info() {
    // will not block if amount of data is small: data are placed to transmit buffer
    Serial2.write(sysex_blm__header, sizeof(sysex_blm__header));
    Serial2.write(0x00);    // device ID
    Serial2.write(0x01);    // Command #1 (Layout Info)
    Serial2.write(0x10);    // Number of columns
    Serial2.write(0x04);    // Number of rows
    Serial2.write(0x02);    // number of LED colours
    Serial2.write(0x00);    // number of extra rows
    Serial2.write(0x00);    // number of extra columns
    Serial2.write(0x00);    // number of extra buttons (e.g. shift)
    Serial2.write(0xF7);    // footer
}
