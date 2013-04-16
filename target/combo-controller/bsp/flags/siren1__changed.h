// =============================================================================
// siren1__changed flag.
// =============================================================================

#ifndef __FLAGS__SIREN1__CHANGED_H
#define __FLAGS__SIREN1__CHANGED_H

#include "util/bitops.h"

#if defined(SIREN1__CHANGED__HOST) && defined(SIREN1__CHANGED__BIT)
DECLARE_BITVAR(siren1__changed, SIREN1__CHANGED__HOST, SIREN1__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(siren1__changed);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void siren1__changed__init(void) {
    siren1__changed__set(0);
}

#endif