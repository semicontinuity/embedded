#ifndef __COMM_SERVICE__ENDPOINT__WATER_VALVE_CONTOLLER_H
#define __COMM_SERVICE__ENDPOINT__WATER_VALVE_CONTOLLER_H

#include "kernel.h"
#include "water_valve_controller.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include CAN_H


inline static void comm_service__endpoint__water_valve_controller__value__handle(const uint8_t is_get) {
    if (is_get) {
        kernel__send_response(sizeof(water_valve_controller__value), (const uint8_t*)&water_valve_controller__value);
    }
    else {
        // Handle PUT request
        water_valve_controller__value__set_from_raw_ptr(&kernel__frame.data);
    }
}

inline static void comm_service__endpoint__water_valve_controller__value__broadcast(void) {
    // It is assumed that the time between valve value changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE, sizeof(water_valve_controller__value), (const uint8_t*)&water_valve_controller__value);
    can__txb1__request_to_send();
}

#endif