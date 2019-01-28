// =============================================================================
// The driver for 4 dry contact sensors SENSOR0..SENSOR3 (normally reading 0).
// All sensors must be connected to the same port SENSORS.
// =============================================================================
#include "drivers/in/sensors.h"

struct sensors__status sensors__status;

/**
 * Called periodically to scan water leak sensors.
 * Sensors readings are filtered.
 * Will invoke the callback water_leak_sensors_scanner__status__on_change() when any of the sensors has changed state.
 */
void sensors__run(void) {
    uint8_t sensors_state = sensors__read();
    uint8_t prev_state = sensors__status.prev_state;
    uint8_t filtered_state = sensors_state & prev_state;
    uint8_t state = sensors__status.state;

    sensors__status.prev_state = sensors_state;
    sensors__status.state = filtered_state;
    if (filtered_state != state) sensors__status__on_change();
}
