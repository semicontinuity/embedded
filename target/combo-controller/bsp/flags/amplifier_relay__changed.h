// =============================================================================
// amplifier_relay__changed flag.
// =============================================================================

#ifndef __FLAGS__AMPLIFIER_RELAY__CHANGED_H
#define __FLAGS__AMPLIFIER_RELAY__CHANGED_H

#include "util/bitops.h"

#if defined(AMPLIFIER_RELAY__CHANGED__HOST) && defined(AMPLIFIER_RELAY__CHANGED__BIT)
DECLARE_BITVAR(amplifier_relay__changed, AMPLIFIER_RELAY__CHANGED__HOST, AMPLIFIER_RELAY__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(amplifier_relay__changed);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void amplifier_relay__changed__init(void) {
    amplifier_relay__changed__set(0);
}

#endif