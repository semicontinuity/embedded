// =============================================================================
// notifications_pending__water_valve flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__WATER_VALVE_H
#define __FLAGS__NOTIFICATIONS_PENDING__WATER_VALVE_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__WATER_VALVE__HOST) && defined(NOTIFICATIONS_PENDING__WATER_VALVE__BIT)
DECLARE_BITVAR(notifications_pending__water_valve, NOTIFICATIONS_PENDING__WATER_VALVE__HOST, NOTIFICATIONS_PENDING__WATER_VALVE__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__water_valve);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__water_valve__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__WATER_VALVE);
}

#endif