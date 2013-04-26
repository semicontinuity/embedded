#ifndef __COMM_SERVICE__ENDPOINT__ALARM__AUTH_H
#define __COMM_SERVICE__ENDPOINT__ALARM__AUTH_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"

#include "services/alarm__auth.h"


inline static void comm_service__endpoint__alarm__auth__handle(const uint8_t is_get) {
    if (is_get) {
        kernel__send_response(alarm__auth__password.length, alarm__auth__password.data);
    }
}

#endif