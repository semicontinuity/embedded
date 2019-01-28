// =============================================================================
// The driver for 8 motion sensors.
// The sensors must connected to the same port.
// Sensors are reading 0 when active.
// =============================================================================

#ifndef __DRIVERS__IN__MOTION_SENSORS_H
#define __DRIVERS__IN__MOTION_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

#define MOTION_SENSORS__MASK (0xFF)


inline static void motion_sensors__init(void) {
    USE_PORT_AS_INPUT(IN__MOTION_SENSORS);
    ENABLE_PULLUPS(IN__MOTION_SENSORS);
}

inline static uint8_t motion_sensors__read(void) {
    return PORT_VALUE(IN__MOTION_SENSORS) & MOTION_SENSORS__MASK;
}


#endif