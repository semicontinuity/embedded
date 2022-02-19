#include "leds_backlight.h"
#include <avr/io.h>


#if defined(LEDS_BACKLIGHT__REFRESH__HOST) && defined(LEDS_BACKLIGHT__REFRESH__HOST)
DEFINE_BITVAR(leds_backlight__refresh, LEDS_BACKLIGHT__REFRESH__HOST, LEDS_BACKLIGHT__REFRESH__BIT);
#endif



bool leds_backlight__refresh__thread__is_runnable(void) {
    return __builtin_expect(leds_backlight__refresh__is_set(), false);
}

void leds_backlight__refresh__thread__run(void) {
    __asm__ __volatile__("leds_backlight__refresh__thread__run:");
    gp_buffer__start();

    // ...

    leds_backlight__refresh__set(0);
}
