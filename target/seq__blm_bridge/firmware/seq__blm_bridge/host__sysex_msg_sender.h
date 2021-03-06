#ifndef __HOST__SYSEX_MSG_SENDER
#define __HOST__SYSEX_MSG_SENDER

#include <Arduino.h>
#include <stdint.h>
#include "seq__blm_bridge__config.h"
#include "midi_sender.h"


static const unsigned char host__sysex_msg_sender__packet__ack[] = {
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x0f,                       // ack_code
        0x00,                       // ack_arg
};

static const unsigned char host__sysex_msg_sender__packet__disack_invalid_command[] = {
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x0e,                       // disack_code
        0x0c,                       // SYSEX_DISACK_INVALID_COMMAND
};

static const unsigned char host__sysex_msg_sender__packet__layout_info[] = {
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x01,                       // Command #1 (Layout Info)
        NUM_BOARDS_X * 4,  // Number of columns
        NUM_BOARDS_Y * 4,  // Number of rows
        0x02,                       // number of LED colours
        0x00,                       // number of extra rows
        0x00,                       // number of extra columns
        0x00,                       // number of extra buttons (e.g. shift)
};


void host__sysex_msg_sender__send_ack(midi_port_t port) {
    midi_sender__send_sysex_message(
            port,
            const_cast<uint8_t *>(host__sysex_msg_sender__packet__ack),
            sizeof(host__sysex_msg_sender__packet__ack)
    );
}

void host__sysex_msg_sender__send_disack_invalid_command(midi_port_t port) {
    midi_sender__send_sysex_message(
            port,
            const_cast<uint8_t *>(host__sysex_msg_sender__packet__disack_invalid_command),
            sizeof(host__sysex_msg_sender__packet__disack_invalid_command)
    );
}

void host__sysex_msg_sender__send_layout_info(midi_port_t port) {
    midi_sender__send_sysex_message(
            port,
            const_cast<uint8_t *>(host__sysex_msg_sender__packet__layout_info),
            sizeof(host__sysex_msg_sender__packet__layout_info)
    );
}

#endif