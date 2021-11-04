#include "leds_bar__data.h"

uint8_t leds_bar__data[4] __attribute__((aligned(4)));

#ifdef LEDS_BAR__DATA__INDEX__REG
register volatile uint8_t leds_bar__data__index asm(QUOTE(LEDS_BAR__DATA__INDEX__REG));
#else
volatile uint8_t leds_bar__data__index;
#endif


void leds_bar__data__put_position_reset(void) {
    leds_bar__data__index = 0;
}

bool leds_bar__data__put(const uint8_t value) {
    __asm__ __volatile__("leds_bar__data__put:");
    if (leds_bar__data__index < 2) {
        if (leds_bar__data__index++ == 0) {
            leds_bar__data[0] = value;
            return true;
        } else {
            leds_bar__data[1] = value;
            return true;
        }
    } else {
        if (leds_bar__data__index++ == 2) {
            leds_bar__data[2] = value;
            return true;
        } else {
            leds_bar__data[3] = value;
            return false;
        }
    }
}