// =============================================================================
// The driver for two water leak sensors WATER_LEAK_SENSOR1 and WATER_LEAK_SENSOR2 (active low).
// The sensors must connected to the same port.
// =============================================================================

#ifndef __WATER_LEAK_SENSORS_H
#define __WATER_LEAK_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void water_leak_sensor1__init(void) {
    USE_AS_INPUT(WATER_LEAK_SENSOR1);
    ENABLE_PULLUP(WATER_LEAK_SENSOR1);
}

inline void water_leak_sensor2__init(void) {
    USE_AS_INPUT(WATER_LEAK_SENSOR2);
    ENABLE_PULLUP(WATER_LEAK_SENSOR2);
}


/**
 * Initialize the button pins.
 */
inline void water_leak_sensors__init(void) {
    water_leak_sensor1__init();
    water_leak_sensor2__init();
}


#endif