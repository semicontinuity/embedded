// =============================================================================
// Communications service.
//
// Services incoming requests.
// =============================================================================
#ifndef __COMM_SERVICE_H
#define __COMM_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

extern volatile mcp251x_message_buffer comm_service__buffer;

void comm_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data);


#endif