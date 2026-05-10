// =============================================================================
// The scanner service for 2 water leak sensors
// at pins WATER_LEAK_SENSOR1 and WATER_LEAK_SENSOR2.
// (Sensors must connected to the same port.)
// =============================================================================
#include "water_leak_sensors_scanner.h"

struct water_leak_sensors_scanner__status water_leak_sensors_scanner__status = {
    .state	= WATER_LEAK_SENSORS_SCANNER__STATE__INACTIVE,
    .prev_state = WATER_LEAK_SENSORS_SCANNER__STATE__INACTIVE
};

/**
 * Called periodically to scan water leak sensors.
 * Sensors readings are filtered.
 * Will invoke the callback water_leak_sensors_scanner__status__on_change() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__run(void) {
    uint8_t sensors_state = water_leak_sensors__read();
    uint8_t prev_state = water_leak_sensors_scanner__status.prev_state;
    uint8_t filtered_state = sensors_state | prev_state;
    uint8_t state = water_leak_sensors_scanner__status.state;

    water_leak_sensors_scanner__status.prev_state = sensors_state;
    water_leak_sensors_scanner__status.state = filtered_state;
    if (filtered_state != state) water_leak_sensors_scanner__status__on_change();
}
