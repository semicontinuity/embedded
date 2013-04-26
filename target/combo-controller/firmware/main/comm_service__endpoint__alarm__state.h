#ifndef __COMM_SERVICE__ENDPOINT__ALARM__STATE_H
#define __COMM_SERVICE__ENDPOINT__ALARM__STATE_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"

#include "services/alarm.h"


inline static void comm_service__endpoint__alarm__state__handle(const uint8_t is_get) {
    if (!is_get) {
        
    }
    else {
        // POST request
        // data[0]: 0=DISARM, 1=ARM - corresponds to values of alarm__state
        uint8_t new_state = kernel__frame.data[0];
        if (new_state == ALARM__STATE__DISARMED) {
            alarm__disarm();
        }
        else if (new_state == ALARM__STATE__ARMING) {
            alarm__arm();
        }
    }
    kernel__send_response(sizeof(alarm__state), &alarm__state);
}

#endif