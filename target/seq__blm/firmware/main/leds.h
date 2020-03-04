#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

extern uint8_t leds__palette[128 * 3];
extern uint8_t leds__data[16 * 3];
extern uint8_t leds__selectors[16];

void leds__init(void);

void leds__refresh(void);

void leds__run(void);

#endif
