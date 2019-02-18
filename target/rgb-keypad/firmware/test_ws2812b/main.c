// =============================================================================
// WS2812B test - blinking LED.
// =============================================================================

#include <util/delay.h>
#include "drivers/comm/ws2812b.h"


struct cRGB led[1];

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
    for(;;) {
        led[0].r=255;led[0].g=00;led[0].b=0;    // Write red to array
        ws2812_setleds(led,1);
        _delay_ms(500);                         // wait for 500ms.

        led[0].r=0;led[0].g=255;led[0].b=0;			// green
        ws2812_setleds(led,1);
        _delay_ms(500);

        led[0].r=0;led[0].g=00;led[0].b=255;		// blue
        ws2812_setleds(led,1);
        _delay_ms(500);
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
