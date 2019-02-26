// =============================================================================
// Test pin change interrupts
// =============================================================================

#include <util/delay.h>
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


void application__init(void) {
    led1__init();
    led2__init();
    led3__init();

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
}


void pin_change_int0__run(void) {
    led1__toggle();
}

void pin_change_int1__run(void) {
    led1__toggle();
}

void pin_change_int2__run(void) {
    led2__toggle();
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
