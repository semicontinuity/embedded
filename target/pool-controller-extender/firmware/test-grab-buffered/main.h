// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>
#include <stdint.h>

// =============================================================================
// Handlers
// =============================================================================

inline void tx_ring_buffer__not_empty__set(bool value) {
}

inline bool tx_ring_buffer__not_empty__is_set(void) {
    return true;
}

inline void tx_ring_buffer__not_full__set(bool value) {
}

inline bool tx_ring_buffer__not_full__is_set(void) {
    return true;
}

void pool_controller__on_lcd_event(const uint8_t value);


#endif
