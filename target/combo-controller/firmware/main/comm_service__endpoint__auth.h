#ifndef __COMM_SERVICE__ENDPOINT__AUTH_H
#define __COMM_SERVICE__ENDPOINT__AUTH_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"

#include "auth_server.h"


inline static void comm_service__endpoint__auth__handle(const uint8_t is_get) {
    if (is_get) {
        kernel__send_response(auth_server__password.length, auth_server__password.data);
    }
}

#endif