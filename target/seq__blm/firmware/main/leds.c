// =============================================================================
// Support for WS2812 LEDs.
// =============================================================================

#include <cpu/avr/asm.h>
#include "leds.h"
#include "drivers/comm/ws2812b.h"

#include "util/bitops.h"


uint8_t leds__data[LEDS__COUNT * 3];


#ifdef LEDS__DATA__PTR__REG
register volatile uint8_t* leds__data__ptr asm(QUOTE(LEDS__DATA__PTR__REG));
#else
volatile uint8_t* leds__data__ptr;
#endif

#if defined(LEDS__REFRESH__HOST) && defined(LEDS__REFRESH__BIT)
DEFINE_BITVAR(leds__refresh, LEDS__REFRESH__HOST, LEDS__REFRESH__BIT);
#else
volatile uint8_t leds__refresh;
DEFINE_BITVAR(leds__refresh, leds__refresh, 0);
#endif


void leds__data__position__set(const uint8_t position) {
    leds__data__ptr = leds__data + position;
}

void leds__data__put(const uint8_t value) {
    // optimize it
    *leds__data__ptr++ = value;
}

void leds__refresh(void) {
    leds__refresh__set(1);
}

void leds__run(void) {
    if (leds__refresh__is_set()) {
        ws2812_sendarray_mask((uint8_t *) leds__data, LEDS__COUNT * 3, _BV(1));
        leds__refresh__set(0);
    }
}

void leds__init(void) {
    leds__refresh__set(0);
}
