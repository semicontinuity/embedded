#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT0), SIGNAL_PIN(DISPLAY_SEGMENT_DP));

/*
#include <stdint.h>
register uint8_t r4 asm("r4");

void r4__set(const uint8_t value) {
    asm volatile("" :"+r"(r4));
    r4 = value;
}

uint8_t r4__get(void) {
    asm volatile("" :"+r"(r4));
    return r4;
}
*/