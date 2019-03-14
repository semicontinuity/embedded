// =============================================================================
// WS2812B explorer.
// =============================================================================


#include <avr/interrupt.h>

#include "services/console.h"
#include "services/console__in.h"
#include "services/console_ws2812b.h"
#include "services/ws2812b_renderer.h"


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    ws2812b_renderer__init();
    console__init();
    console__in__init();
    console__ws2812b__init();
}

void application__start(void) {
    console__start();
    console__in__start();
}



// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        console__read_line();
        console__ws2812b__run();
        if (ws2812b_renderer__is_runnable()) {
            ws2812b_renderer__run();
        }
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
