// =============================================================================
// MODBUS server.
// =============================================================================
#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include <stdbool.h>

void modbus_server__init(void);

bool modbus_server__run(void);

#endif