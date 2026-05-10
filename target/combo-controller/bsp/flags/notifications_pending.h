// =============================================================================
// notifications_pending flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING_H
#define __FLAGS__NOTIFICATIONS_PENDING_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__HOST) && defined(NOTIFICATIONS_PENDING__BIT)
DEFINE_BITVAR(notifications_pending, NOTIFICATIONS_PENDING__HOST, NOTIFICATIONS_PENDING__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending);
#endif


#endif