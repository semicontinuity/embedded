#include <stdint.h>
#include "sysex_handler.h"
#include "sysex_handler_blm_callbacks.h"

static uint8_t sysex_blm__command;
static uint8_t sysex_blm__command_length;



void sysex__data(uint8_t data) {
    if (!sysex_blm__command_length) {
        sysex_blm__command = data;
    }
    ++sysex_blm__command_length;
}


void sysex__finish() {
    if (sysex_blm__command_length == 1) {
        switch (sysex_blm__command) {
            case 0x00:
                sysex_blm__handle_request_layout_info();
                break;
            case 0x01: // Layout Info
            case 0x0e: // error
                // ignore to avoid feedback loops
                break;
            case 0x0f:
                sysex_blm__handle_ping();
                break;
            default:
                sysex_blm__handle_invalid_command();
        }
    } else {
        sysex_blm__handle_invalid_command();
    }
    sysex_blm__command_length = 0;
}


void sysex__error() {
    sysex_blm__handle_invalid_command();
    sysex_blm__command_length = 0;
}