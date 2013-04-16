// =============================================================================
// water_valve__changed flag.
// =============================================================================

#ifndef __FLAGS__WATER_VALVE__CHANGED_H
#define __FLAGS__WATER_VALVE__CHANGED_H

#include "util/bitops.h"

#if defined(WATER_VALVE__CHANGED__HOST) && defined(WATER_VALVE__CHANGED__BIT)
DECLARE_BITVAR(water_valve__changed, WATER_VALVE__CHANGED__HOST, WATER_VALVE__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(water_valve__changed);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void water_valve__changed__init(void) {
    water_valve__changed__set(0);
}

#endif