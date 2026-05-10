// =============================================================================
// Remote switch MODBUS server: counters and server callbacks.
// =============================================================================
#ifndef SERVICES__MODBUS_SERVER_H
#define SERVICES__MODBUS_SERVER_H

#include <stdint.h>

extern volatile uint16_t valid_frames_received;
extern volatile uint16_t invalid_frames_received;
extern volatile uint16_t frames_sent;
extern volatile uint16_t protocol_errors;
extern volatile uint16_t buffer_overflows;

#endif
