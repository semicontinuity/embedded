#ifndef __COMM_SERVICE__BUTTONS_SCANNER_H
#define __COMM_SERVICE__BUTTONS_SCANNER_H

#include "kernel.h"
#include "buttons_scanner.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include CAN_H


inline static void comm_service__buttons_scanner__status__handle(const uint8_t is_get) {
    if (is_get) {
        kernel__send_response(sizeof(buttons_scanner__status), (const uint8_t*)&buttons_scanner__status);
    }
    // Ignore PUT requests
}

inline static void comm_service__buttons_scanner__status__broadcast(void) {
    // It is assumed that the time between pin changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb2__load_data((const uint8_t*)&buttons_scanner__status, sizeof(buttons_scanner__status));
    can__txb2__request_to_send();
}

#endif