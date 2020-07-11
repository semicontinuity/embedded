#include <stdint.h>
#include "host__sysex_msg_handler__callbacks.h"


typedef enum {
    RECEIVING_HEADER_AND_COMMAND    = 0,
    RECEIVED_HEADER_AND_COMMAND     = 1,
    RECEIVED_SYSEX_END              = 2,
    RECEIVED_INVALID_COMMAND        = 3
} host__sysex_msg_handler__state_t;

static uint8_t host__sysex_msg_handler__state = 0;
static uint8_t host__sysex_msg_handler__length = 0;
static uint8_t host__sysex_msg_handler__command;

// SYSEX START + manfacturer header + device ID 0
static const uint8_t host__sysex_msg_handler__command_header[1 + 5] = {0xf0, 0x00, 0x00, 0x7e, 0x4e, 0x00 };

uint8_t host__sysex_msg_handler__command_payload[768] = {};


void host__sysex_msg_handler__on_sysex_data(uint8_t data) {
    if (host__sysex_msg_handler__state == RECEIVING_HEADER_AND_COMMAND) {
        if (host__sysex_msg_handler__length < sizeof(host__sysex_msg_handler__command_header)) {
            if (data != host__sysex_msg_handler__command_header[host__sysex_msg_handler__length++]) {
                host__sysex_msg_handler__state = RECEIVED_INVALID_COMMAND;
            }
        } else  {
            host__sysex_msg_handler__state = RECEIVED_HEADER_AND_COMMAND;
            host__sysex_msg_handler__command = data;
            host__sysex_msg_handler__length = 0;
        }
    } else if (host__sysex_msg_handler__state == RECEIVED_HEADER_AND_COMMAND) {
        if (data < 0x80u) {
            host__sysex_msg_handler__command_payload[host__sysex_msg_handler__length++] = data;
        } else if (data == 0xF7u) {
            host__sysex_msg_handler__state = RECEIVED_SYSEX_END;
        } else {
            host__sysex_msg_handler__state = RECEIVED_INVALID_COMMAND;
        }
    } else {
        host__sysex_msg_handler__state = RECEIVED_INVALID_COMMAND;
    }
}


void host__sysex_msg_handler__on_sysex_finish() {
    if (host__sysex_msg_handler__state == RECEIVED_SYSEX_END && host__sysex_msg_handler__length == 0) {
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
    } else if (host__sysex_msg_handler__state == RECEIVED_SYSEX_END && host__sysex_msg_handler__command >= 0x10 && host__sysex_msg_handler__command <= 0x1F) {
        host__sysex_msg_handler__handle_set_palette_data(
                host__sysex_msg_handler__command - 0x10,
                host__sysex_msg_handler__command_payload,
                host__sysex_msg_handler__length
        );
    } else {
        host__sysex_msg_handler__handle_invalid_command();
    }
    host__sysex_msg_handler__length = 0;
    host__sysex_msg_handler__state = 0;
}
