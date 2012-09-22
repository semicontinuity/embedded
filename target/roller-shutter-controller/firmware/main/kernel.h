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

struct kernel__status {
    uint16_t watchdog_reset_count;
    uint16_t brownout_reset_count;
    uint16_t rx_error_count;
    uint16_t tx_error_count;
};
extern struct kernel__status kernel__status __attribute__((section(".noinit")));


extern volatile mcp251x_message_buffer kernel__frame __attribute__((section(".noinit")));

extern void kernel__send_response(const uint8_t count, const uint8_t* data) __attribute__((section(".kernel")));


#endif