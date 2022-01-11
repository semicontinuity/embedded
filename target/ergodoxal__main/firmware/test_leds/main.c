// =============================================================================
// Firmware for Ergodoxial keyboard: test LEDs
// =============================================================================

#include <avr/interrupt.h>
#include "cpu/avr/usart0.h"
#include "comm_inbound.h"


#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>
#include <drivers/out/led_c.h>

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    comm_inbound__init();
//    usart0__init();
}

void application__start(void) {
//    comm_inbound__thread__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

//    sei();

    led_a__set(1);
    led_b__set(1);
    led_c__set(1);

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    __asm__ __volatile__("main__loop:");
    for(;;) {
        __asm__ __volatile__("main__loop__3:");
//        if (comm_inbound__thread__is_runnable()) {
//            comm_inbound__thread__run();
//        }
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
