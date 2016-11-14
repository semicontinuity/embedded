// =============================================================================
// MODBUS RTU driver.
// Direction control module.
// =============================================================================
#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__DIR_CONTROL_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__DIR_CONTROL_H

#include <stdbool.h>


/** Initialize the direction control line, must be put into RX mode */
void modbus_rtu_driver__dir_control__init(void);

void modbus_rtu_driver__dir_control__tx(void);

void modbus_rtu_driver__dir_control__rx(void);

#endif