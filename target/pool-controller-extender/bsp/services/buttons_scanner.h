// =============================================================================
// Buttons scanner service.
// =============================================================================

#ifndef __SERVICES__BUTTONS_SCANNER_H
#define __SERVICES__BUTTONS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

/**
 * Initialize the buttons scanner.
 */
void buttons_scanner__init(void);

/**
 * Return the latest state of the buttons.
 */
uint8_t buttons_scanner__state__get(void);

/**
 * Callback to be implemented by user.
 * Invoked when the state of the buttons has changed.
 */
void buttons_scanner__status__on_change(const uint8_t pins_changed);

/**
 * Called periodically to scan buttons.
 * Will invoke the callback buttons_scanner__status__on_change() when any of the buttons has changed state.
 */
inline static void buttons_scanner__run(void);

#endif
