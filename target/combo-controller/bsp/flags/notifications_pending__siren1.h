// =============================================================================
// notifications_pending__siren1 flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__SIREN1_H
#define __FLAGS__NOTIFICATIONS_PENDING__SIREN1_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__SIREN1__HOST) && defined(NOTIFICATIONS_PENDING__SIREN1__BIT)
DECLARE_BITVAR(notifications_pending__siren1, NOTIFICATIONS_PENDING__SIREN1__HOST, NOTIFICATIONS_PENDING__SIREN1__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__siren1);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__siren1__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__SIREN1);
}

#endif