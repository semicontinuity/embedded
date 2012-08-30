// =============================================================================
// Communications service.
// =============================================================================
#ifndef __COMM_SERVICE_H
#define __COMM_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

extern volatile mcp251x_message_buffer comm_service__buffer;

/**
 * Initializes the service.
 * Must be provided by implementation.
 */
inline static /*abstract */ void comm_service__rx__init(void);

/**
 * Starts the service.
 * Must be provided by implementation.
 */
inline static /*abstract */ void comm_service__rx__start(void);


void comm_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data);


#endif