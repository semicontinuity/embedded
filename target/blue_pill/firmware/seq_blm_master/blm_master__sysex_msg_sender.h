#ifndef __BLM_MASTER__SYSEX_MSG_SENDER
#define __BLM_MASTER__SYSEX_MSG_SENDER

#include <Arduino.h>
#include <stdint.h>
#include "seq_blm_master__config.h"
#include "blm_master__sysex_msg_sender__arduino_serial.h"
#include "blm_master__sysex_msg_sender__usb_midi.h"


static const unsigned char blm_master__sysex_msg_sender__packet__ack[] = {
        0xf0,                       // SYSEX START
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x0f,                       // ack_code
        0x00,                       // ack_arg
        0xF7,                       // SYSEX END
};

static const unsigned char blm_master__sysex_msg_sender__packet__disack_invalid_command[] = {
        0xf0,                       // SYSEX START
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x0e,                       // disack_code
        0x0c,                       // SYSEX_DISACK_INVALID_COMMAND
        0xF7,                       // SYSEX END
};

static const unsigned char blm_master__sysex_msg_sender__packet__layout_info[] = {
        0xf0,                       // SYSEX START
        0x00, 0x00, 0x7e, 0x4e,     // header
        0x00,                       // device ID
        0x01,                       // Command #1 (Layout Info)
        BLM_SCALAR_NUM_BOARDS_X*4,  // Number of columns
        BLM_SCALAR_NUM_BOARDS_Y*4,  // Number of rows
        0x02,                       // number of LED colours
        0x00,                       // number of extra rows
        0x00,                       // number of extra columns
        0x00,                       // number of extra buttons (e.g. shift)
        0xF7,                       // SYSEX END
};


void blm_master__sysex_msg_sender__send(uint8_t *payload, uint32 length) {
    blm_master__sysex_msg_sender__arduino_serial__send(payload, length);
    blm_master__sysex_msg_sender__usb_midi__send(payload, length);
}


void blm_master__sysex_msg_sender__send_ack() {
    blm_master__sysex_msg_sender__send(
            const_cast<uint8_t *>(blm_master__sysex_msg_sender__packet__ack),
            sizeof(blm_master__sysex_msg_sender__packet__ack)
    );
}

void blm_master__sysex_msg_sender__send_disack_invalid_command() {
    blm_master__sysex_msg_sender__send(
            const_cast<uint8_t *>(blm_master__sysex_msg_sender__packet__disack_invalid_command),
            sizeof(blm_master__sysex_msg_sender__packet__disack_invalid_command)
    );
}

void blm_master__sysex_msg_sender__send_layout_info() {
    blm_master__sysex_msg_sender__send(
            const_cast<uint8_t *>(blm_master__sysex_msg_sender__packet__layout_info),
            sizeof(blm_master__sysex_msg_sender__packet__layout_info)
    );
}

#endif