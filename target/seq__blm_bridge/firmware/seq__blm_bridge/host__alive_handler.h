#ifndef __HOST__ALIVE_HANDLER
#define __HOST__ALIVE_HANDLER

#include <Arduino.h>
#include "seq__blm_bridge__config.h"
#include "host__sysex_msg_handler__callbacks.h"
#include "host__sysex_msg_sender.h"
#include "midi_port.h"

midi_port_t host__alive_handler__host_cable = MIDI_PORT_UNDEFINED;
uint32_t host__alive_handler__last_rx_millis = 0;
uint32_t host__alive_handler__last_tx_millis = 0;



void host__alive_handler__host_connected__set(const midi_port_t host) {
    host__alive_handler__last_rx_millis = millis();
    host__alive_handler__host_cable = host;
    digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_ON);
}

midi_port_t host__alive_handler__host_connected__get() {
    return host__alive_handler__host_cable;
}


bool host__alive_handler__is_runnable() {
    return millis() - host__alive_handler__last_tx_millis > 5000;
}

void host__alive_handler__run() {
    if (host__alive_handler__host_cable) {
        host__sysex_msg_sender__send_ack(host__alive_handler__host_cable);
    } else {
        host__sysex_msg_sender__send_layout_info(MIDI_PORT_UNDEFINED);
    }
    host__alive_handler__last_tx_millis = millis();
    if (host__alive_handler__host_cable != MIDI_PORT_UNDEFINED) {
        if (host__alive_handler__last_tx_millis - host__alive_handler__last_rx_millis > 5000) {
            host__alive_handler__host_cable = MIDI_PORT_UNDEFINED;
            digitalWrite(PIN_LED_HOST_CONNECTED, PIN_LED_HOST_CONNECTED_OFF);
        }
    }
}

#endif