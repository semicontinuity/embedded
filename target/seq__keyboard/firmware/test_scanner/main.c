// =============================================================================
// Test scanning
// =============================================================================

#include <avr/interrupt.h>
#include "services/scanner.h"
#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"
#include "data.h"


void application__init(void) {
    data__rgb_leds[0*3 + 0x00] = 0x1f;
    data__rgb_leds[0*3 + 0x01] = 0x00;
    data__rgb_leds[0*3 + 0x02] = 0x00;

    data__rgb_leds[1*3 + 0x00] = 0x9f;
    data__rgb_leds[1*3 + 0x01] = 0x00;
    data__rgb_leds[1*3 + 0x02] = 0x00;


    data__rgb_leds[2*3 + 0x00] = 0x3f;
    data__rgb_leds[2*3 + 0x01] = 0x00;
    data__rgb_leds[2*3 + 0x02] = 0x00;

    data__rgb_leds[3*3 + 0x00] = 0xbf;
    data__rgb_leds[3*3 + 0x01] = 0x00;
    data__rgb_leds[3*3 + 0x02] = 0x00;


    data__rgb_leds[4*3 + 0x00] = 0x5f;
    data__rgb_leds[4*3 + 0x01] = 0x00;
    data__rgb_leds[4*3 + 0x02] = 0x00;

    data__rgb_leds[5*3 + 0x00] = 0xdf;
    data__rgb_leds[5*3 + 0x01] = 0x00;
    data__rgb_leds[5*3 + 0x02] = 0x00;


    data__rgb_leds[6*3 + 0x00] = 0x7f;
    data__rgb_leds[6*3 + 0x01] = 0x00;
    data__rgb_leds[6*3 + 0x02] = 0x00;

    data__rgb_leds[7*3 + 0x00] = 0xff;
    data__rgb_leds[7*3 + 0x01] = 0x00;
    data__rgb_leds[7*3 + 0x02] = 0x00;


    scanner__init();
}

void application__start(void) {
    scanner__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
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
