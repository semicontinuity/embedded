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

bool data__leds__put(const uint8_t value) {
    if (data__leds__index < 2) {
        if (data__leds__index++ == 0) {
            data__leds[0] = value;
            return true;
        } else {
            data__leds[1] = value;
            return true;
        }
    } else {
        if (data__leds__index++ == 2) {
            data__leds[2] = value;
            return true;
        } else {
            data__leds[3] = value;
            return false;
        }
    }
}