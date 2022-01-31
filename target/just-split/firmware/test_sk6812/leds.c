// =============================================================================
// Support for WS2812 LEDs.
// Define ws2812_port, ws2812_pin.
// The pin is kept low between transmissions, so LEDs are kept in reset.
// As a consequence, the interval between LED updates must be at least 50uS.
// =============================================================================

#include <cpu/avr/asm.h>
#include "leds.h"
#include "drivers/comm/ws2812b.h"

#include "util/bitops.h"

uint8_t leds__data[16 * 3];


#if defined(LEDS__REFRESH__HOST) && defined(LEDS__REFRESH__BIT)
DEFINE_BITVAR(leds__refresh, LEDS__REFRESH__HOST, LEDS__REFRESH__BIT);
#else
volatile uint8_t leds__refresh;

void leds__refresh__set(char v) { leds__refresh = v;}
bool leds__refresh__is_set(void) { return (leds__refresh); }
char leds__refresh__get(void) { return (leds__refresh); }
#endif


void leds__run(void) {
    __asm__ __volatile__("leds__run:");
    if (leds__refresh__is_set()) {
        leds__refresh__set(0);
        __asm__ __volatile__("leds__run__before_send:");
        ws2812_sendarray_mask(LEDS__COUNT * 3, _BV(ws2812_pin));
        __asm__ __volatile__("leds__run__after_send:");
    }
}

void leds__init(void) {
    ws2812_DDRREG |= _BV(ws2812_pin);
    leds__refresh__set(0);
}
