// =============================================================================
// alarm__state__changed flag.
// =============================================================================

#ifndef __FLAGS__ALARM__STATE__CHANGED_H
#define __FLAGS__ALARM__STATE__CHANGED_H

#include "util/bitops.h"

#if defined(ALARM__STATE__CHANGED__HOST) && defined(ALARM__STATE__CHANGED__BIT)
DECLARE_BITVAR(ALARM__STATE__changed, ALARM__STATE__CHANGED__HOST, ALARM__STATE__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(alarm__state__changed);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void alarm__state__changed__init(void) {
    alarm__state__changed__set(0);
}

#endif