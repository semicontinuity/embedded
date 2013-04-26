// =============================================================================
// The scanner service for motion sensors
// at port MOTION_SENSOR.
// (Sensors must connected to the same port.)
// =============================================================================
#include "motion_sensors_scanner.h"

struct motion_sensors_scanner__status motion_sensors_scanner__status = {
    .state	= MOTION_SENSORS_SCANNER__STATE__INACTIVE,
    .prev_state = MOTION_SENSORS_SCANNER__STATE__INACTIVE
};

/**
 * Called periodically to scan motion sensors.
 * Sensors readings are filtered.
 * Will invoke the callback motion_sensors_scanner__status__on_change() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__run(void) {
    uint8_t sensors_state = motion_sensors__read();
    uint8_t prev_state = motion_sensors_scanner__status.prev_state;
    uint8_t filtered_state = sensors_state | prev_state;
    uint8_t state = motion_sensors_scanner__status.state;

    motion_sensors_scanner__status.prev_state = sensors_state;
    motion_sensors_scanner__status.state = filtered_state;
    if (filtered_state != state) motion_sensors_scanner__status__on_change();
}
