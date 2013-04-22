// =============================================================================
// motion_sensors__changed flag.
// =============================================================================

#ifndef __FLAGS__MOTION_SENSORS__CHANGED_H
#define __FLAGS__MOTION_SENSORS__CHANGED_H

#include "util/bitops.h"

#if defined(MOTION_SENSORS__CHANGED__HOST) && defined(MOTION_SENSORS__CHANGED__BIT)
DECLARE_BITVAR(motion_sensors__changed, MOTION_SENSORS__CHANGED__HOST, MOTION_SENSORS__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(motion_sensors__changed);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void motion_sensors__changed__init(void) {
    motion_sensors__changed__set(0);
}

#endif