#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include "util/bitops.h"

/** Contains color data, 3 bytes per LED, in native format (GRB?) */
extern uint8_t leds__data[LEDS__COUNT * 3];

DECLARE_BITVAR(leds__refresh);

void leds__init(void);

void leds__run(void);

#endif
