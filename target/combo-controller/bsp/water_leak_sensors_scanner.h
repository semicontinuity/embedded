// =============================================================================
// The scanner service for 2 water leak sensors
// at pins WATER_LEAK_SENSOR1 and WATER_LEAK_SENSOR2.
// Sensors must connected to the same port and read logical 1 when not active.
// =============================================================================
#ifndef __WATER_LEAK_SENSORS_SCANNER_H
#define __WATER_LEAK_SENSORS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>
#include <stdbool.h>


#define WATER_LEAK_SENSORS_SCANNER__STATE__INACTIVE     (SIGNAL_MASK(WATER_LEAK_SENSOR1) | SIGNAL_MASK(WATER_LEAK_SENSOR2))


struct water_leak_sensors_scanner__status {
    uint8_t state;
    uint8_t prev_state;
};
extern struct water_leak_sensors_scanner__status water_leak_sensors_scanner__status;


/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void);



inline void water_leak_sensors_scanner__init(void) {
}


/**
 * Called periodically to scan water leak sensors.
 * Sensors readings are filtered.
 * Will invoke the callback water_leak_sensors_scanner__status__on_change() when any of the sensors has changed state.
 */
inline static void water_leak_sensors_scanner__run(void) {
    uint8_t sensors_state = PORT_VALUE(WATER_LEAK_SENSORS) & WATER_LEAK_SENSORS_SCANNER__STATE__INACTIVE;
    uint8_t prev_state = water_leak_sensors_scanner__status.prev_state;
    uint8_t filtered_state = sensors_state | prev_state;
    uint8_t state = water_leak_sensors_scanner__status.state;

    water_leak_sensors_scanner__status.prev_state = sensors_state;
    water_leak_sensors_scanner__status.state = filtered_state;
    if (filtered_state != state) water_leak_sensors_scanner__status__on_change();
}


/** Returns true when at least one sensor is active, i.e. water leak detected */
inline static bool water_leak_sensors_scanner__is_active(void) {
    return water_leak_sensors_scanner__status.state != WATER_LEAK_SENSORS_SCANNER__STATE__INACTIVE;
}

#endif