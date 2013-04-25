#ifndef __COMM_SERVICE__ENDPOINT__SENSORS_H
#define __COMM_SERVICE__ENDPOINT__SENSORS_H

#include "drivers/in/sensors.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include CAN_H


INLINE void comm_service__endpoint__sensors__handle(const uint8_t message_type) {
    if (message_type == CANP_MSG_TYPE_GET) {
        
    }
}

INLINE void comm_service__endpoint__sensors__send(void) {
    can__txb1__load_report(CANP_REPORT__SENSORS__STATE, 1, (const uint8_t*)&sensors__status.state);
    can__txb1__request_to_send();
}


#endif