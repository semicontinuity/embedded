// =============================================================================
// notifications_pending__security__state flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__SECURITY__STATE_H
#define __FLAGS__NOTIFICATIONS_PENDING__SECURITY__STATE_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__SECURITY__STATE__HOST) && defined(NOTIFICATIONS_PENDING__SECURITY__STATE__BIT)
DECLARE_BITVAR(notifications_pending__security__state, NOTIFICATIONS_PENDING__SECURITY__STATE__HOST, NOTIFICATIONS_PENDING__SECURITY__STATE__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__security__state);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__security__state__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__SECURITY__STATE);
}

#endif