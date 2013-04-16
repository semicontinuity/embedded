// =============================================================================
// gpio_notifications__pending flag.
// =============================================================================

#ifndef __FLAGS__GPIO_NOTIFICATIONS__PENDING_H
#define __FLAGS__GPIO_NOTIFICATIONS__PENDING_H

#include "util/bitops.h"

#if defined(GPIO_NOTIFICATIONS__PENDING__HOST) && defined(GPIO_NOTIFICATIONS__PENDING__BIT)
DECLARE_BITVAR(gpio_notifications__pending, GPIO_NOTIFICATIONS__PENDING__HOST, GPIO_NOTIFICATIONS__PENDING__BIT);
#else
DECLARE_FAKE_BITVAR(gpio_notifications__pending);
#endif


/**
 * Sets the initial value of the flag.
 */
inline static void gpio_notifications__pending__init(void) {
    gpio_notifications__pending__set(0);
}

#endif