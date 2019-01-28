// =============================================================================
// LEDs scanner service.
// =============================================================================

#include "services/leds_scanner.h"
#include "drivers/io/leds_tap.h"
#include "cpu/avr/asm.h"


#ifdef LEDS_SCANNER__STATE__REG
register uint8_t leds_scanner__state asm(QUOTE(LEDS_SCANNER__STATE__REG));
#else
volatile uint8_t leds_scanner__state;
#endif


/**
 * Initialize the leds scanner.
 */
void leds_scanner__init(void) {
    leds_scanner__state = 0;
}

/**
 * Return the latest state of LEDs.
 */
uint8_t leds_scanner__state__get(void) {
    return leds_scanner__state;
}


/**
 * Called periodically to scan leds.
 * Will invoke the callback leds_scanner__status__on_change() when any of the leds has changed state.
 */
void leds_scanner__run(void) {
    const uint8_t current_state = leds_tap__get() & LEDS_TAP__MASK;

    const uint8_t leds_scanner__pins_changed = leds_scanner__state ^ current_state;
    if (leds_scanner__pins_changed != 0) {
        leds_scanner__state = current_state;
        leds_scanner__status__on_change(leds_scanner__pins_changed);
    }
}
