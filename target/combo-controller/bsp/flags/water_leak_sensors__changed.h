// =============================================================================
// water_leak_sensors__changed flag.
// =============================================================================

#ifndef __FLAGS__WATER_LEAK_SENSORS__CHANGED_H
#define __FLAGS__WATER_LEAK_SENSORS__CHANGED_H

#include "util/bitops.h"

#if defined(WATER_LEAK_SENSORS__CHANGED__HOST) && defined(WATER_LEAK_SENSORS__CHANGED__BIT)
DECLARE_BITVAR(water_leak_sensors__changed, WATER_LEAK_SENSORS__CHANGED__HOST, WATER_LEAK_SENSORS__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(water_leak_sensors__changed);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void water_leak_sensors__changed__init(void) {
    water_leak_sensors__changed__set(0);
}

#endif