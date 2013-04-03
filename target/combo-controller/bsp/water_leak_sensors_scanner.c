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
