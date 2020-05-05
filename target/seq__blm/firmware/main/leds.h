#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include "util/bitops.h"

/** Contains color palette, it is possible to define 128 colors */
extern uint8_t leds__palette[128 * 3];

/** Contains color data, 3 bytes per LED, in native format (GRB?) */
extern uint8_t leds__data[16 * 3];

/** Contains color data, 1 byte per LED; valid values are 0-127; selects entry from leds__palette */
extern uint8_t leds__selectors[16];

DECLARE_BITVAR(leds__refresh);

void leds__init(void);

void leds__run(void);

#endif
