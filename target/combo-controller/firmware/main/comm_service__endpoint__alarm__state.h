#ifndef __COMM_SERVICE__ENDPOINT__ALARM__STATE_H
#define __COMM_SERVICE__ENDPOINT__ALARM__STATE_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "endpoints/alarm__state.h"
#include <stdint.h>


inline static void comm_service__endpoint__alarm__state__handle(const uint8_t message_type) {
    if (message_type == CANP_MSG_TYPE_GET) {
        uint8_t *data;
        uint8_t length = alarm__state__get_data(&data);
        kernel__send_response(length, data);
    }
    else if (message_type == CANP_MSG_TYPE_POST) {
        // POST request
        // data[0]: 0=DISARM, 1=ARM - corresponds to values of alarm__state
        alarm__state__set_data(kernel__frame.data);
    }
}

#endif