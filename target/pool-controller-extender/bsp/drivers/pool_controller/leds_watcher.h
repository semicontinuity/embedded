// =============================================================================
// The driver for 3 watched LEDS.
// =============================================================================

#ifndef __DRIVERS__POOL_CONTROLLER__LEDS_WATCHER_H
#define __DRIVERS__POOL_CONTROLLER__LEDS_WATCHER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize LEDs watcher.
 */
void leds_watcher__init(void);


#endif