#include <stdint.h>
#include <Wire.h>
#include "midi_parser__callbacks__sysex_msg.h"

static TwoWire *bridge__sysex_handler__wire;

static uint8_t bridge__sysex_handler__state;
/* 0: receiving address; 1: receiving high nibble; 2: receiving low nibble; other: error */
static uint8_t bridge__sysex_handler__command[32];
static uint8_t bridge__sysex_handler__command_length;
static uint8_t bridge__sysex_handler__address;

static int8_t bridge__sysex_handler__parse_nibble(uint8_t data) {
    if (data >= 'A' && data <= 'F')
        return data - 'A' + 0x0A;
    if (data >= 'a' && data <= 'f')
        return data - 'A' + 0x0a;
    if (data >= '0' && data <= '9')
        return data - '0';
    return -1;
}

static void bridge__sysex_handler__reset() {
    bridge__sysex_handler__state = 0;
    bridge__sysex_handler__command_length = 0;
}

void bridge__sysex_handler__init(TwoWire * wire) {
    bridge__sysex_handler__wire = wire;
}


// Implementation of midi_parser__callbacks__sysex_msg.h
// -----------------------------------------------------------------------------


void midi_parser__on_sysex_data(uint8_t data) {
    switch (bridge__sysex_handler__state) {
        case 0: {
            // receiving address
            bridge__sysex_handler__address = data;
            bridge__sysex_handler__state = 1;
            break;
        }
        case 1: {
            // receiving high nibble
            // TODO check size
            int8_t h_nibble = bridge__sysex_handler__parse_nibble(data);
            if (h_nibble >= 0) {
                bridge__sysex_handler__command[bridge__sysex_handler__command_length] = ((uint8_t)h_nibble << 4U);
                bridge__sysex_handler__state = 2;
            } else {
                bridge__sysex_handler__state = -1;
            }

            break;
        }
        case 2: {
            // receiving low nibble
            int8_t l_nibble = bridge__sysex_handler__parse_nibble(data);
            if (l_nibble >= 0) {
                bridge__sysex_handler__command[bridge__sysex_handler__command_length++] |= (uint8_t) l_nibble;
                bridge__sysex_handler__state = 1;
            } else {
                bridge__sysex_handler__state = -1;
            }
            break;
        }
    }
}


void midi_parser__on_sysex_finish() {
    // may signal error with LED
    if (bridge__sysex_handler__state == 1) {
        bridge__sysex_handler__wire->beginTransmission(bridge__sysex_handler__address);
        for (int i = 0; i < bridge__sysex_handler__command_length; i++) {
            bridge__sysex_handler__wire->write(bridge__sysex_handler__command[i]);
        }
        bridge__sysex_handler__wire->endTransmission(bridge__sysex_handler__address);
    }
    bridge__sysex_handler__reset();
}

void midi_parser__on_sysex_error() {
    bridge__sysex_handler__reset();
}
