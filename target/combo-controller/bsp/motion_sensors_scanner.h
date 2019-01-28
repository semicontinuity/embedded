// =============================================================================
// The scanner service for motion sensors
// at port MOTION_SENSOR.
// Sensors must connected to the same port and read logical 1 when not active.
// =============================================================================
#ifndef __MOTION_SENSORS_SCANNER_H
#define __MOTION_SENSORS_SCANNER_H

#include "drivers/in/motion_sensors.h"
#include "cpu/avr/gpio.h"
#include <stdint.h>
#include <stdbool.h>


#define MOTION_SENSORS_SCANNER__STATE__INACTIVE MOTION_SENSORS__MASK


struct motion_sensors_scanner__status {
    uint8_t state;
    uint8_t prev_state;
};
extern struct motion_sensors_scanner__status motion_sensors_scanner__status;


/**
 * Callback function, called by motion_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__status__on_change(void);



inline void motion_sensors_scanner__init(void) {}


/**
 * Called periodically to scan motion sensors.
 * Sensors readings are filtered.
 * Will invoke the callback motion_sensors_scanner__status__on_change() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__run(void);

/**
 * This procedure is called when motion sensor is active.
 */
INLINE void motion_sensors_scanner__out__run(void);


/** Returns true when at least one sensor is active, i.e. motion detected */
inline static bool motion_sensors_scanner__is_active(void) {
    return motion_sensors_scanner__status.state != MOTION_SENSORS_SCANNER__STATE__INACTIVE;
}

#endif