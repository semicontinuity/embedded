// =============================================================================
// Communications service.
//
// Abstract.
// Implementations must provide:
// - comm_service__rx__init()
// - comm_service__rx__start()
// =============================================================================
#ifndef __COMM_SERVICE_H
#define __COMM_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

extern volatile mcp251x_message_buffer comm_service__packet __attribute__((section(".kernel.data")));

extern void comm_service__send_response(const uint8_t count, const uint8_t* data) __attribute__((section(".kernel")));


#endif