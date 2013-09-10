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

bool modbus_rtu_driver__on_frame_received(void);


#endif