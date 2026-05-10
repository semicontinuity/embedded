// =============================================================================
// password__changed flag.
// =============================================================================

#ifndef __FLAGS__PASSWORD__CHANGED_H
#define __FLAGS__PASSWORD__CHANGED_H

#include "util/bitops.h"

#if defined(PASSWORD__CHANGED__HOST) && defined(PASSWORD__CHANGED__BIT)
DEFINE_BITVAR(password__changed, PASSWORD__CHANGED__HOST, PASSWORD__CHANGED__BIT);
#else
DECLARE_FAKE_BITVAR(password__changed);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void password__changed__init(void) {
    password__changed__set(0);
}

#endif