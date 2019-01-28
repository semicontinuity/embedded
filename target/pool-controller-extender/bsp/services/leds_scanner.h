// =============================================================================
// LEDs scanner service.
// =============================================================================

#ifndef __SERVICES__LEDS_SCANNER_H
#define __SERVICES__LEDS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

/**
 * Initialize the leds scanner.
 */
void leds_scanner__init(void);

/**
 * Return the latest state of LEDs.
 */
uint8_t leds_scanner__state__get(void);

/**
 * Callback to be implemented by user.
 * Invoked when the state of the leds has changed.
 */
void leds_scanner__status__on_change(const uint8_t pins_changed);

/**
 * Called periodically to scan leds.
 * Will invoke the callback leds_scanner__status__on_change() when any of the leds has changed state.
 */
inline static void leds_scanner__run(void);

#endif
