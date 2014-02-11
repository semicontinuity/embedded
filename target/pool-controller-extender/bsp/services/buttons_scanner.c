// =============================================================================
// Buttons scanner service.
// =============================================================================

#include "services/buttons_scanner.h"
#include "drivers/io/buttons_tap.h"
#include "cpu/avr/asm.h"


#ifdef BUTTONS_SCANNER__STATE__REG
register uint8_t buttons_scanner__state asm(QUOTE(BUTTONS_SCANNER__STATE__REG));
#else
volatile uint8_t buttons_scanner__state;
#endif


/**
 * Initialize the buttons scanner.
 */
void buttons_scanner__init(void) {
    buttons_scanner__state = 0;
}

/**
 * Return the latest state of the buttons.
 */
uint8_t buttons_scanner__state__get(void) {
    return buttons_scanner__state;
}


/**
 * Called periodically to scan buttons.
 * Will invoke the callback buttons_scanner__status__on_change() when any of the buttons has changed state.
 */
void buttons_scanner__run(void) {
    const uint8_t current_state = buttons_tap__get() & BUTTONS_TAP__MASK;
    const uint8_t buttons_scanner__pins_changed = buttons_scanner__state ^ current_state;
    if (buttons_scanner__pins_changed != 0) {
        buttons_scanner__state = current_state;
        buttons_scanner__status__on_change(buttons_scanner__pins_changed);
    }
}
