#include <stdint.h>
#include "midi_parser__callbacks__sysex_msg.h"
#include "blm_master__sysex_msg_handler__callbacks.h"

static uint8_t blm_master__sysex_handler__command;
static uint8_t blm_master__sysex_handler__command_length;


// Implementation of midi_parser_callbacks__sysex_msg.h
// -----------------------------------------------------------------------------

void midi_parser__on_sysex_data(uint8_t data) {
    if (!blm_master__sysex_handler__command_length) {
        blm_master__sysex_handler__command = data;
    }
    ++blm_master__sysex_handler__command_length;
}


void midi_parser__on_sysex_finish() {
    if (blm_master__sysex_handler__command_length == 1) {
        switch (blm_master__sysex_handler__command) {
            case 0x00:
                blm_master__sysex_handler__handle_request_layout_info();
                break;
            case 0x01: // Layout Info
            case 0x0e: // error
                // ignore to avoid feedback loops
                break;
            case 0x0f:
                blm_master__sysex_handler__handle_ping();
                break;
            default:
                blm_master__sysex_handler__handle_invalid_command();
        }
    } else {
        blm_master__sysex_handler__handle_invalid_command();
    }
    blm_master__sysex_handler__command_length = 0;
}


void midi_parser__on_sysex_error() {
    blm_master__sysex_handler__handle_invalid_command();
    blm_master__sysex_handler__command_length = 0;
}