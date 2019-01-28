// =============================================================================
// The driver for two water leak sensors,
// IN__WATER_LEAK_SENSOR1 and IN__WATER_LEAK_SENSOR2.
// The sensors must connected to the same port.
// Sensors are reading 0 when active.
// =============================================================================

#ifndef __DRIVERS__IN__WATER_LEAK_SENSORS_H
#define __DRIVERS__IN__WATER_LEAK_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


#define WATER_LEAK_SENSORS__MASK (SIGNAL_MASK(IN__WATER_LEAK_SENSOR1) | SIGNAL_MASK(IN__WATER_LEAK_SENSOR2))


inline void water_leak_sensor1__init(void) {
    USE_AS_INPUT(IN__WATER_LEAK_SENSOR1);
    ENABLE_PULLUP(IN__WATER_LEAK_SENSOR1);
}

inline void water_leak_sensor2__init(void) {
    USE_AS_INPUT(IN__WATER_LEAK_SENSOR2);
    ENABLE_PULLUP(IN__WATER_LEAK_SENSOR2);
}


/**
 * Initialize the button pins.
 */
inline void water_leak_sensors__init(void) {
    water_leak_sensor1__init();
    water_leak_sensor2__init();
}


inline static uint8_t water_leak_sensors__read(void) {
    return PORT_VALUE(IN__WATER_LEAK_SENSORS) & WATER_LEAK_SENSORS__MASK;
}

#endif