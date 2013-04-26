// =============================================================================
// The driver for 8 motion sensors.
// The sensors must connected to the same port.
// Sensors are reading 0 when active.
// =============================================================================

#ifndef __IN__MOTION_SENSORS_H
#define __IN__MOTION_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void in__motion_sensors__init(void) {
    USE_PORT_AS_INPUT(IN__MOTION_SENSORS);
    ENABLE_PULLUPS(IN__MOTION_SENSORS);
}


#endif