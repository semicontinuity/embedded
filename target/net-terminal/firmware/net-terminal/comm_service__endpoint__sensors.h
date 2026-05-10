#ifndef __COMM_SERVICE__ENDPOINT__SENSORS_H
#define __COMM_SERVICE__ENDPOINT__SENSORS_H

#include "drivers/in/sensors.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "drivers/net/can/mcp251x/tx.h"
#include "kernel.h"


INLINE void comm_service__endpoint__sensors__handle(const uint8_t message_type) {
    if (message_type == CANP_MSG_TYPE_GET) {
        kernel__send_response(1, (const uint8_t*)&sensors__status.state);        
    }
}

INLINE void comm_service__endpoint__sensors__send(void) {
    mcp2515__tx__txb1__load_report(CANP_REPORT__SENSORS__STATE, 1, (const uint8_t*)&sensors__status.state);
    mcp2515__tx__txb1__request_to_send();
}


#endif