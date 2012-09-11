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
    // It is assumed that the time between motor mode changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), it's better to abort the transmission in progress
    // and/or increase some error counter.
    // Just try to send. If the transmission is in progress, this will be no-op.
    can__txb2__load_report(CANP_REPORT__BUTTONS_SCANNER__STATUS, sizeof(buttons_scanner__status), (const uint8_t*)&buttons_scanner__status);
    can__txb2__request_to_send();
}

#endif