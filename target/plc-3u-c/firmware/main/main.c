// =============================================================================
// Relay for 6 signals: BUTTON[i] -> LED[i]
// =============================================================================

#include "drivers/in/button1.h"
#include "drivers/in/button2.h"
#include "drivers/in/button3.h"
#include "drivers/in/button4.h"
#include "drivers/in/button5.h"
#include "drivers/in/button6.h"

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"
#include "drivers/out/led5.h"
#include "drivers/out/led6.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    ENABLE_PULLUP(UNUSED_D0);
    ENABLE_PULLUP(UNUSED_D1);
    ENABLE_PULLUP(UNUSED_D2);
    ENABLE_PULLUP(UNUSED_D3);
    ENABLE_PULLUP(UNUSED_D4);
    ENABLE_PULLUP(UNUSED_B3);
    ENABLE_PULLUP(UNUSED_B4);
    ENABLE_PULLUP(UNUSED_B5);

    button1__init();
    button2__init();
    button3__init();
    button4__init();
    button5__init();
    button6__init();

    led1__init();
    led2__init();
    led3__init();
    led4__init();
    led5__init();
    led6__init();
}

static void application__start(void) {
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
        led1__set(button1__get());
        led2__set(button2__get());
        led3__set(button3__get());
        led4__set(button4__get());
        led5__set(button5__get());
        led6__set(button6__get());
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
