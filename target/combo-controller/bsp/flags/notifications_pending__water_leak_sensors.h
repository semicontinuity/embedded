// =============================================================================
// notifications_pending__water_leak_sensors flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS_H
#define __FLAGS__NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS__HOST) && defined(NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS__BIT)
DECLARE_BITVAR(notifications_pending__water_leak_sensors, NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS__HOST, NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__water_leak_sensors);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__water_leak_sensors__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__WATER_LEAK_SENSORS);
}

#endif