// =============================================================================
// WS2812B test.
// =============================================================================

#include <util/delay.h>
#include "drivers/comm/ws2812b.h"


uint8_t led[16*3];
uint8_t *led_ptr = led;


void application__init(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

    _delay_ms(500);                         // wait for 500ms.

    *led_ptr++ = 0x10;
    *led_ptr++ = 0x20;
    *led_ptr++ = 0x00;
    ws2812_sendarray_mask(led, 3, _BV(1));

    for(;;) {
    }

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
