#include <stdint.h>
#include "host__sysex_msg_handler__callbacks.h"

uint8_t host__sysex_msg_handler__command_payload[768] = {};
static const uint8_t host__sysex_msg_handler__command_header[1 + 5] = {0xf0, 0x00, 0x00, 0x7e, 0x4e, 0x00 }; // SYSEX Header + device ID 0
static uint8_t host__sysex_msg_handler__command;
static uint8_t host__sysex_msg_handler__command_length = 0;
static uint8_t host__sysex_msg_handler__command_header_matched = 0;


void host__sysex_msg_handler__on_sysex_data(uint8_t data) {
    if (host__sysex_msg_handler__command_length < sizeof(host__sysex_msg_handler__command_header)) {
        if (data != host__sysex_msg_handler__command_header[host__sysex_msg_handler__command_length]) {
            host__sysex_msg_handler__command_header_matched = 0;
        }
    } else if (host__sysex_msg_handler__command_length == sizeof(host__sysex_msg_handler__command_header)) {
        host__sysex_msg_handler__command_header_matched = 1;
        host__sysex_msg_handler__command = data;
    } else {
        int32_t offset = host__sysex_msg_handler__command_length - sizeof(host__sysex_msg_handler__command_header) - 1;
        host__sysex_msg_handler__command_payload[offset] = data;
    }
    ++host__sysex_msg_handler__command_length;
}


void host__sysex_msg_handler__on_sysex_finish() {
    if (host__sysex_msg_handler__command_header_matched && host__sysex_msg_handler__command_length == sizeof(host__sysex_msg_handler__command_header) + 1) {
        switch (host__sysex_msg_handler__command) {
            case 0x00:
                host__sysex_msg_handler__handle_request_layout_info();
                break;
            case 0x01: // Layout Info
            case 0x0e: // error
                // ignore to avoid feedback loops
                break;
            case 0x0f:
                host__sysex_msg_handler__handle_ping();
                break;
            default:
                host__sysex_msg_handler__handle_invalid_command();
        }
    } else if (host__sysex_msg_handler__command_header_matched && host__sysex_msg_handler__command >= 0x10 && host__sysex_msg_handler__command <= 0x1F) {
        host__sysex_msg_handler__handle_set_palette_data(
                host__sysex_msg_handler__command - 0x10,
                host__sysex_msg_handler__command_payload,
                host__sysex_msg_handler__command_length - sizeof(host__sysex_msg_handler__command_header) - 1
        );
    } else {
        host__sysex_msg_handler__handle_invalid_command();
    }
    host__sysex_msg_handler__command_length = 0;
    host__sysex_msg_handler__command_header_matched = 0;
}


void host__sysex_msg_handler__on_sysex_error() {
    host__sysex_msg_handler__handle_invalid_command();
    host__sysex_msg_handler__command_length = 0;
    host__sysex_msg_handler__command_header_matched = 0;
}
