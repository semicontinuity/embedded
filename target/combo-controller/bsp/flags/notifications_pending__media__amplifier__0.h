// =============================================================================
// notifications_pending__media__amplifier__0 flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0_H
#define __FLAGS__NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0__HOST) && defined(NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0__BIT)
DECLARE_BITVAR(notifications_pending__media__amplifier__0, NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0__HOST, NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__media__amplifier__0);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__media__amplifier__0__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__MEDIA__AMPLIFIER__0);
}

#endif