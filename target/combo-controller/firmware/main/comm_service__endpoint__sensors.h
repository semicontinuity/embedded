#ifndef __COMM_SERVICE__ENDPOINT__SENSORS_H
#define __COMM_SERVICE__ENDPOINT__SENSORS_H

#include "services/alarm.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "kernel.h"


INLINE void comm_service__endpoint__sensors__handle_value(void) {
    if (kernel__frame.data[0] != 0) alarm__sensor_active();
}


#endif