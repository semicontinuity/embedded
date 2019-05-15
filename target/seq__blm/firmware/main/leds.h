#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

void leds__init(void);

void leds__data__position__set(uint8_t position);

void leds__data__put(uint8_t value);

void leds__refresh(void);

void leds__run(void);

#endif
