#include "leds_bar__data.h"

uint8_t leds_bar__data[4] __attribute__((aligned(4)));

#ifdef LEDS_BAR__DATA__PTR__REG
register volatile uint8_t* leds_bar__data__ptr asm(QUOTE(LEDS_BAR__DATA__PTR__REG));
#else
#  ifdef LEDS_BAR__DATA__INDEX__REG
register volatile uint8_t leds_bar__data__index asm(QUOTE(LEDS_BAR__DATA__INDEX__REG));
#  else
volatile uint8_t leds_bar__data__index;
#  endif
#endif


void leds_bar__data__put_position_reset(void) {
#ifdef LEDS_BAR__DATA__PTR__REG
    leds_bar__data__ptr = leds_bar__data;
#else
    leds_bar__data__index = 0;
#endif
}

bool leds_bar__data__put(const uint8_t value) {
#if defined(LEDS_BAR__DATA__PTR__REG) && LEDS_BAR__DATA__PTR__REG==26
    STORE_XPLUS(leds_bar__data__ptr, value);
#elif defined(LEDS_BAR__DATA__PTR__REG) && LEDS_BAR__DATA__PTR__REG==28
    STORE_YPLUS(leds_bar__data__ptr, value);
#elif defined(LEDS_BAR__DATA__PTR__REG) && LEDS_BAR__DATA__PTR__REG==30
    STORE_ZPLUS(leds_bar__data__ptr, value);
#else
    // For the case, when all pointer registers are occupied
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
#endif
}
