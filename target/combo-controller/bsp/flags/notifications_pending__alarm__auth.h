// =============================================================================
// notifications_pending__alarm__auth flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__ALARM__AUTH_H
#define __FLAGS__NOTIFICATIONS_PENDING__ALARM__AUTH_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__ALARM__AUTH__HOST) && defined(NOTIFICATIONS_PENDING__ALARM__AUTH__BIT)
DECLARE_BITVAR(notifications_pending__alarm__auth, NOTIFICATIONS_PENDING__ALARM__AUTH__HOST, NOTIFICATIONS_PENDING__ALARM__AUTH__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__alarm__auth);
#endif

/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__alarm__auth__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__ALARM__AUTH);
}

#endif