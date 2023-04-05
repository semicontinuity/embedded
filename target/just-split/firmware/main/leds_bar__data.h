#ifndef LEDS_BAR__DATA_H
#define LEDS_BAR__DATA_H

#include <stdint.h>
#include <stdbool.h>

extern volatile uint8_t leds_bar__data[4];

void leds_bar__data__put_position_reset(void);

bool leds_bar__data__put(uint8_t value);


#endif
