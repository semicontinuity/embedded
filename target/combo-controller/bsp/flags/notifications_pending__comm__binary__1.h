// =============================================================================
// notifications_pending__comm_binary__1 flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__COMM__BINARY__1_H
#define __FLAGS__NOTIFICATIONS_PENDING__COMM__BINARY__1_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__COMM__BINARY__1__HOST) && defined(NOTIFICATIONS_PENDING__COMM__BINARY__1__BIT)
DEFINE_BITVAR(notifications_pending__comm__binary__1, NOTIFICATIONS_PENDING__COMM__BINARY__1__HOST, NOTIFICATIONS_PENDING__COMM__BINARY__1__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__comm__binary__1);
#endif


#endif