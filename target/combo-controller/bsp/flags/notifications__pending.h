// =============================================================================
// notifications__pending flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS__PENDING_H
#define __FLAGS__NOTIFICATIONS__PENDING_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS__PENDING__HOST) && defined(NOTIFICATIONS__PENDING__BIT)
DECLARE_BITVAR(notifications__pending, NOTIFICATIONS__PENDING__HOST, NOTIFICATIONS__PENDING__BIT);
#else
DECLARE_FAKE_BITVAR(notifications__pending);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications__pending__init(void) {
    notifications__pending__set(0);
}

#endif