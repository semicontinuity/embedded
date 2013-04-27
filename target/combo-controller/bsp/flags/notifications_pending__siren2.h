// =============================================================================
// notifications_pending__siren2 flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__SIREN2_H
#define __FLAGS__NOTIFICATIONS_PENDING__SIREN2_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__SIREN2__HOST) && defined(NOTIFICATIONS_PENDING__SIREN2__BIT)
DECLARE_BITVAR(notifications_pending__siren2, NOTIFICATIONS_PENDING__SIREN2__HOST, NOTIFICATIONS_PENDING__SIREN2__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__siren2);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__siren2__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__SIREN2);
}

#endif