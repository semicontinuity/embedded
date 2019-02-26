// =============================================================================
// Test pin change interrupts
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>

#include "led1.h"
#include "led2.h"
#include "led3.h"

#include "keyboard__pins.h"
#include "keyboard__interrupts.h"


void application__init(void) {
    keyboard__pins__init();

    led1__init();
    led2__init();
    led3__init();

    keyboard__interrupts__init();
}


void application__start(void) {
    keyboard__interrupts__start();
}


void pin_change_int0__run(void) {
    led1__toggle();
}

void pin_change_int1__run(void) {
    led2__toggle();
}

void pin_change_int2__run(void) {
    led3__toggle();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_us(2);
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
