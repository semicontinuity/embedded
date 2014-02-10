// =============================================================================
// The driver for 3 watched LEDS.
// =============================================================================

#ifndef __DRIVERS__IO__LEDS_TAP_H
#define __DRIVERS__IO__LEDS_TAP_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize LEDs tap.
 */
void leds_tap__init(void);

/**
 * Read the LEDs state.
 */
uint8_t leds_tap__get(void);


#endif