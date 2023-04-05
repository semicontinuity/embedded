#include "leds_backlight.h"
#include <avr/io.h>
#include "drivers/comm/ws2812b.h"



#if defined(LEDS_BACKLIGHT__REFRESH__HOST) && defined(LEDS_BACKLIGHT__REFRESH__HOST)
DEFINE_BITVAR(leds_backlight__refresh, LEDS_BACKLIGHT__REFRESH__HOST, LEDS_BACKLIGHT__REFRESH__BIT);
#endif


void leds_backlight__init(void) {
    ws2812_DDRREG |= _BV(ws2812_pin);
}


bool leds_backlight__refresh__thread__is_runnable(void) {
    return __builtin_expect(leds_backlight__refresh__is_set(), false);
}

void leds_backlight__refresh__thread__run(void) {
    __asm__ __volatile__("leds_backlight__refresh__thread__run:");
    leds_backlight__refresh__set(0);
    cli();
    ws2812_sendarray_mask(gp_buffer__data, LEDS_BACKLIGHT__COUNT*3, _BV(ws2812_pin));
    sei();
}
