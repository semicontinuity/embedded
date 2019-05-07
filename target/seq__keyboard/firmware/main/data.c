#include "data.h"
#include <cpu/avr/macros.h>

uint8_t data__leds[4] __attribute__((aligned(4)));

#ifdef DATA__LEDS__INDEX__REG
register uint8_t data__leds__index asm(QUOTE(DATA__LEDS__INDEX__REG));
#else
volatile uint8_t data__leds__index;
#endif


void data__leds__put_position_reset(void) {
    data__leds__index = 0;
}

void data__leds__put(const uint8_t value) {
    data__leds[data__leds__index++] = value;
}