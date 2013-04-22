// =============================================================================
// Kernel, handler for TX complete events.
// =============================================================================
#ifndef __KERNEL__TX__HANDLER_H
#define __kERNEL__TX__HANDLER_H

#include <stdint.h>
#include "kernel__handler__spi.h"


static inline void kernel__tx__handle(const uint8_t event) {
    kernel__out__handle(event, 0);
}

#endif