// =============================================================================
// Test pin change interrupts
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include "led1.h"
#include "led2.h"
#include "led3.h"
#include "drivers/in/button1.h"
#include "drivers/in/button2.h"
#include "drivers/in/button3.h"
#include "drivers/in/button4.h"
#include "drivers/in/button5.h"
#include "drivers/in/button6.h"
#include "drivers/in/button7.h"
#include "drivers/in/button8.h"
#include "drivers/in/button9.h"
#include "drivers/in/button10.h"
#include "drivers/in/button11.h"
#include "drivers/in/button12.h"
#include "drivers/in/button13.h"
#include "drivers/in/button14.h"
#include "drivers/in/button15.h"
#include "drivers/in/button16.h"
#include "cpu/avr/pin_change_int0.h"
#include "cpu/avr/pin_change_int1.h"
#include "cpu/avr/pin_change_int2.h"


uint8_t pin_change_int0__mask(void) {
    // Pin Change Interrupt 0 serves PB0..PB7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xB
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xB
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xB
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xB
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xB
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xB
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xB
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xB
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xB
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xB
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xB
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xB
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xB
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xB
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xB
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xB
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}

void pin_change_int0__init(void) {
    pin_change_int0__mask__set(pin_change_int0__mask());
}


uint8_t pin_change_int1__mask(void) {
    // Pin Change Interrupt 1 serves PC0..PC6
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xC
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xC
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xC
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xC
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xC
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xC
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xC
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xC
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xC
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xC
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xC
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xC
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xC
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xC
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xC
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xC
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}

void pin_change_int1__init(void) {
    pin_change_int1__mask__set(pin_change_int1__mask());
}


uint8_t pin_change_int2__mask(void) {
    // Pin Change Interrupt 1 serves PD0..PD7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xD
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xD
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xD
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xD
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xD
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xD
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xD
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xD
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xD
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xD
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xD
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xD
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xD
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xD
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xD
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xD
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}

void pin_change_int2__init(void) {
    pin_change_int2__mask__set(pin_change_int2__mask());
}


void application__init(void) {
    button1__init();
    button2__init();
    button3__init();
    button4__init();
    button5__init();
    button6__init();
    button7__init();
    button8__init();
    button9__init();
    button10__init();
    button11__init();
    button12__init();
    button13__init();
    button14__init();
    button15__init();
    button16__init();

    led1__init();
    led2__init();
    led3__init();

    pin_change_int0__init();
    pin_change_int1__init();
    pin_change_int2__init();
}


void application__start(void) {
    pin_change_int0__start();
    pin_change_int1__start();
    pin_change_int2__start();
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
