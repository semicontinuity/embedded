// =============================================================================
// notifications_pending__amplifier_relay flag.
// =============================================================================

#ifndef __FLAGS__NOTIFICATIONS_PENDING__AMPLIFIER_RELAY_H
#define __FLAGS__NOTIFICATIONS_PENDING__AMPLIFIER_RELAY_H

#include "util/bitops.h"

#if defined(NOTIFICATIONS_PENDING__AMPLIFIER_RELAY__HOST) && defined(NOTIFICATIONS_PENDING__AMPLIFIER_RELAY__BIT)
DECLARE_BITVAR(notifications_pending__amplifier_relay, NOTIFICATIONS_PENDING__AMPLIFIER_RELAY__HOST, NOTIFICATIONS_PENDING__AMPLIFIER_RELAY__BIT);
#else
DECLARE_FAKE_BITVAR(notifications_pending__amplifier_relay);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void notifications_pending__amplifier_relay__init(void) {
    USE_AS_OUTPUT(NOTIFICATIONS_PENDING__AMPLIFIER_RELAY);
}

#endif