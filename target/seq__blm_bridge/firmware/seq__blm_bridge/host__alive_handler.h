#ifndef __HOST__ALIVE_HANDLER
#define __HOST__ALIVE_HANDLER

#include <Arduino.h>
#include "seq__blm_bridge__config.h"
#include "host__sysex_msg_handler__callbacks.h"
#include "host__sysex_msg_sender.h"


bool host__alive_handler__host_connected = false;
uint32_t host__alive_handler__last_rx_millis = 0;
uint32_t host__alive_handler__last_tx_millis = 0;


bool host__alive_handler__is_host_connected() {
    return host__alive_handler__host_connected;
}

void host__alive_handler__set_host_connected() {
    host__alive_handler__last_rx_millis = millis();
    host__alive_handler__host_connected = true;
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_ON);
}


bool host__alive_handler__is_runnable() {
    return millis() - host__alive_handler__last_tx_millis > 5000;
}

void host__alive_handler__run() {
    if (host__alive_handler__host_connected) {
        host__sysex_msg_sender__send_ack();
    } else {
        host__sysex_msg_sender__send_layout_info();
    }
    host__alive_handler__last_tx_millis = millis();
    if (host__alive_handler__host_connected) {
        if (host__alive_handler__last_tx_millis - host__alive_handler__last_rx_millis > 5000) {
            host__alive_handler__host_connected = false;
            digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);
        }
    }
}

#endif