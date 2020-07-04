#include <stdint.h>
#include "midi_parser__callbacks__sysex_msg.h"
#include "blm_master__sysex_msg_handler__callbacks.h"

uint8_t blm_master__sysex_msg_handler__command_payload[768] = {};
static const uint8_t blm_master__sysex_msg_handler__command_header[1 + 5] = {0xf0, 0x00, 0x00, 0x7e, 0x4e, 0x00 }; // SYSEX Header + device ID 0
static uint8_t blm_master__sysex_msg_handler__command;
static uint8_t blm_master__sysex_msg_handler__command_length = 0;
static uint8_t blm_master__sysex_msg_handler__command_header_matched = 0;


// Implementation of midi_parser__callbacks__sysex_msg.h
// -----------------------------------------------------------------------------

void midi_parser__on_sysex_data(uint8_t data) {
    if (blm_master__sysex_msg_handler__command_length < sizeof(blm_master__sysex_msg_handler__command_header)) {
        if (data != blm_master__sysex_msg_handler__command_header[blm_master__sysex_msg_handler__command_length]) {
            blm_master__sysex_msg_handler__command_header_matched = 0;
        }
    } else if (blm_master__sysex_msg_handler__command_length == sizeof(blm_master__sysex_msg_handler__command_header)) {
        blm_master__sysex_msg_handler__command_header_matched = 1;
        blm_master__sysex_msg_handler__command = data;
    } else {
        int32_t offset = blm_master__sysex_msg_handler__command_length - sizeof(blm_master__sysex_msg_handler__command_header) - 1;
        blm_master__sysex_msg_handler__command_payload[offset] = data;
    }
    ++blm_master__sysex_msg_handler__command_length;
}


void midi_parser__on_sysex_finish() {
    if (blm_master__sysex_msg_handler__command_header_matched && blm_master__sysex_msg_handler__command_length == sizeof(blm_master__sysex_msg_handler__command_header) + 1) {
        switch (blm_master__sysex_msg_handler__command) {
            case 0x00:
                blm_master__sysex_msg_handler__handle_request_layout_info();
                break;
            case 0x01: // Layout Info
            case 0x0e: // error
                // ignore to avoid feedback loops
                break;
            case 0x0f:
                blm_master__sysex_msg_handler__handle_ping();
                break;
            default:
                blm_master__sysex_msg_handler__handle_invalid_command();
        }
    } else if (blm_master__sysex_msg_handler__command_header_matched && blm_master__sysex_msg_handler__command >= 0x10 && blm_master__sysex_msg_handler__command <= 0x1F) {
        blm_master__sysex_msg_handler__handle_set_palette_data(
                blm_master__sysex_msg_handler__command - 0x10,
                blm_master__sysex_msg_handler__command_payload,
                blm_master__sysex_msg_handler__command_length - sizeof(blm_master__sysex_msg_handler__command_header) - 1
        );
    } else {
        blm_master__sysex_msg_handler__handle_invalid_command();
    }
    blm_master__sysex_msg_handler__command_length = 0;
    blm_master__sysex_msg_handler__command_header_matched = 0;
}


void midi_parser__on_sysex_error() {
    blm_master__sysex_msg_handler__handle_invalid_command();
    blm_master__sysex_msg_handler__command_length = 0;
    blm_master__sysex_msg_handler__command_header_matched = 0;
}
