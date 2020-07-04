#ifndef __BLM_MASTER__ALIVE_HANDLER
#define __BLM_MASTER__ALIVE_HANDLER

#include <Arduino.h>
#include "seq_blm_master__config.h"
#include "blm_master__sysex_msg_handler__callbacks.h"
#include "blm_master__sysex_msg_sender.h"


bool blm_master__alive_handler__host_connected = false;
uint32_t blm_master__alive_handler__last_tx_millis = 0;


bool blm_master__alive_handler__is_host_connected() {
    return blm_master__alive_handler__host_connected;
}

void blm_master__alive_handler__set_host_connected() {
    blm_master__alive_handler__last_tx_millis = millis();
    blm_master__alive_handler__host_connected = true;
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_ON);
}


bool blm_master__alive_handler__is_runnable() {
    return millis() - blm_master__alive_handler__last_tx_millis > 5000;
}

void blm_master__alive_handler__run() {
    if (blm_master__alive_handler__host_connected) {
        blm_master__sysex_msg_sender__send_ack();
    } else {
        blm_master__sysex_msg_sender__send_layout_info();
    }
    blm_master__alive_handler__last_tx_millis = millis();
    blm_master__alive_handler__host_connected = false;
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);
}

#endif