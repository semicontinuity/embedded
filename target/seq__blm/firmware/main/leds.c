// =============================================================================
// Support for WS2812 LEDs.
// =============================================================================

#include <cpu/avr/asm.h>
#include "leds.h"
#include "drivers/comm/ws2812b.h"

#include "util/bitops.h"
#include "util/delay.h"

uint8_t leds__data[16 * 3];
uint8_t leds__selectors[16];
uint8_t leds__palette[128 * 3];


#if defined(LEDS__REFRESH__HOST) && defined(LEDS__REFRESH__BIT)
DEFINE_BITVAR(leds__refresh, LEDS__REFRESH__HOST, LEDS__REFRESH__BIT);
#else
volatile uint8_t leds__refresh;
//DEFINE_BITVAR(leds__refresh, leds__refresh, 0);

inline void leds__refresh__set(char v)	{ leds__refresh = v;}
inline bool leds__refresh__is_set(void)	{ return (leds__refresh); }
inline char leds__refresh__get(void)	{ return (leds__refresh); }
#endif


void leds__run(void) {
    __asm__ __volatile__("leds__run:");
    if (leds__refresh__is_set()) {
        leds__refresh__set(0);
//        _delay_ms(10);

        // this is weird
        // with delay AFTER rendering, PACKED4/UNPACK commands work as expected.

        // with no delay,
        // - nothing is rendered, but rendered OK after refresh
        // with small delay,
        // - some LEDs are not rendered (usually 2nd),
        //   and video memory examination reveals that rendering command
        //   has rendered incorrect data to video memory (corresponds to display)
        //
        // faulty MPU? (changed, no effect)
        // unstable power supply, leading to incorrect code execution?
        // register corruption? (got rid of all fixed registers, has not helped)
        // flag corruption?
        // stack corruption? - moving leds__palette to the end has not helped
        // memory corruption?
        // incorrect code generated?
        // some of the above, leading to corruption of the 1st message byte?
        // =======================================================
//        _delay_loop_2(8000);
        // =======================================================
        __asm__ __volatile__("leds__run__before_send:");
        ws2812_sendarray_mask((uint8_t *) leds__data, LEDS__COUNT * 3, _BV(ws2812_pin));
        __asm__ __volatile__("leds__run__after_send:");
    }
}

void leds__init(void) {
    leds__refresh__set(0);
}
