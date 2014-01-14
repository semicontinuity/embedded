// =============================================================================
// notifications_pending__lcd flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__LCD_H
#define __FLAGS__NOTIFICATIONS_PENDING__LCD_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__LCD__HOST) && defined(NOTIFICATIONS_PENDING__LCD__BIT)
DECLARE_BITVAR(notifications_pending__lcd, NOTIFICATIONS_PENDING__LCD__HOST, NOTIFICATIONS_PENDING__LCD__BIT);
#else
#warning "Fake bit variable for notifications_pending__lcd"
DECLARE_FAKE_BITVAR(notifications_pending__lcd);
#endif


#endif