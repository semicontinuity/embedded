// =============================================================================
// MODBUS RTU driver.
// =============================================================================
#ifndef MODBUS_RTU_DRIVER_H
#define MODBUS_RTU_DRIVER_H

#include <stdbool.h>


void modbus_rtu_driver__init(void);

void modbus_rtu_driver__start(void);

bool modbus_rtu_driver__is_runnable(void);

void modbus_rtu_driver__run(void);


// Callback methods to be implemented by user
// -----------------------------------------------------------------------------

/**
 * Invoked by the driver on every received frame
 * @return true if the response must be sent (placed to the same buffer)
 */
bool modbus_rtu_driver__on_frame_received(void);

void modbus_rtu_driver__on_frame_sent(void);

void modbus_rtu_driver__on_protocol_error(void);

void modbus_rtu_driver__on_buffer_overflow(void);


#endif