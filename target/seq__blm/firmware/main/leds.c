// =============================================================================
// Support for WS2812 LEDs.
// =============================================================================

#include "leds.h"
#include "drivers/comm/twi_slave_callbacks.h"
#include "drivers/comm/ws2812b.h"

#include "util/bitops.h"


#if defined(LEDS__REFRESH__HOST) && defined(LEDS__REFRESH__BIT)
DEFINE_BITVAR(leds__refresh, LEDS__REFRESH__HOST, LEDS__REFRESH__BIT);
#else
volatile uint8_t leds__refresh;
DEFINE_BITVAR(leds__refresh, leds__refresh, 0);
#endif


volatile uint8_t *led_ptr;
uint8_t leds[16*3];

void leds__run(void) {
    if (leds__refresh__is_set()) {
        ws2812_sendarray_mask((uint8_t *) leds, 16*3, _BV(1));
        leds__refresh__set(0);
    }
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    *led_ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    leds__refresh__set(1);
    led_ptr = leds;
}

void twi__slave__on_data_reception_aborted(void) {
    led_ptr = leds;
}

void leds__init(void) {
    leds__refresh__set(0);
    led_ptr = leds;
}
