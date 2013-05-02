#ifndef __COMM_SERVICE__ENDPOINT__ALARM__STATE_H
#define __COMM_SERVICE__ENDPOINT__ALARM__STATE_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "endpoints/alarm__state.h"
#include <stdint.h>


inline static void comm_service__endpoint__alarm__state__handle(const uint8_t message_type) {
    if (message_type == CANP_MSG_TYPE_GET) {
        alarm__state__broadcast();
    }
    else if (message_type == CANP_MSG_TYPE_POST) {
        alarm__state__set_data(kernel__frame.data);
    }
}

#endif