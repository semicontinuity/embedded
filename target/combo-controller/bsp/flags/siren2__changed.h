// =============================================================================
// siren2__changed flag.
// =============================================================================

#ifndef __FLAGS__SIREN2__CHANGED_H
#define __FLAGS__SIREN2__CHANGED_H

#include "util/bitops.h"

#if defined(SIREN2__CHANGED__HOST) && defined(SIREN2__CHANGED__BIT)
DECLARE_BITVAR(siren2__changed, SIREN2__CHANGED__HOST, SIREN2__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(siren2__changed);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void siren2__changed__init(void) {
    siren2__changed__set(0);
}

#endif