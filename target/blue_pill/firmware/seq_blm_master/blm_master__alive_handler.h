#include <Arduino.h>
#include "blm_master__sysex_msg_handler__callbacks.h"


bool blm_master__alive_handler__midi_data_received = false;
uint32_t blm_master__alive_handler__last_tx_millis = 0;


void blm_master__alive_handler__midi_channel_msg_received() {
    blm_master__alive_handler__midi_data_received = true;
    digitalWrite(PA1, HIGH);
}


void blm_master__alive_handler__run() {
    uint32 last_ms = blm_master__alive_handler__last_tx_millis;
    uint32 ms = millis();

    if (ms - last_ms > 5000) {
        if (blm_master__alive_handler__midi_data_received) {
            blm_master__sysex_handler__handle_ping();
        } else {
            blm_master__sysex_handler__handle_request_layout_info();
        }
        blm_master__alive_handler__last_tx_millis = ms;
        blm_master__alive_handler__midi_data_received = false;
        digitalWrite(PA1, LOW);
    }
}
