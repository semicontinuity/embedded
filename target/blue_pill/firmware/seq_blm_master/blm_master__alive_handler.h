#ifndef __BLM_MASTER__ALIVE_HANDLER
#define __BLM_MASTER__ALIVE_HANDLER

#include <Arduino.h>
#include "seq_blm_master__config.h"
#include "blm_master__sysex_msg_handler__callbacks.h"
#include "blm_master__sysex_msg_handler__sender.h"


bool blm_master__alive_handler__host_connected = false;
uint32_t blm_master__alive_handler__last_tx_millis = 0;


bool blm_master__alive_handler__is_host_connected() {
    return blm_master__alive_handler__host_connected;
}

void blm_master__alive_handler__midi_channel_msg_received() {
    blm_master__alive_handler__host_connected = true;
    digitalWrite(PIN_LED_HOST_CONNECTED, HIGH);
}


void blm_master__alive_handler__run() {
    uint32 last_ms = blm_master__alive_handler__last_tx_millis;
    uint32 ms = millis();

    if (ms - last_ms > 5000) {
        if (blm_master__alive_handler__host_connected) {
            blm_master__sysex_msg_sender__send_ack();
        } else {
            blm_master__sysex_msg_sender__send_layout_info();
        }
        blm_master__alive_handler__last_tx_millis = ms;
        blm_master__alive_handler__host_connected = false;
        digitalWrite(PIN_LED_HOST_CONNECTED, LOW);
    }
}

#endif