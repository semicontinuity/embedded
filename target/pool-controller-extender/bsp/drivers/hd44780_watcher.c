// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#include "drivers/hd44780_watcher.h"
#include "services/tx_ring_buffer.h"


/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void hd44780_watcher__on_clock(void) {
    if (tx_ring_buffer__not_full__is_set()) {
        tx_ring_buffer__put(0);
    }
}
