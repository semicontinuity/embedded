#ifndef DATA_H
#define DATA_H

#include <stdint.h>

extern uint8_t data__leds[4];

void data__leds__put_position_reset(void);

void data__leds__put(uint8_t value);


#endif
