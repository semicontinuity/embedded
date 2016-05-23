// =============================================================================
// Remote switch - test keyboard.
// =============================================================================

#include "cpu/avr/wdt.h"

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include <avr/interrupt.h>
#include <util/delay.h>


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    led1__init();
    led2__init();
    led3__init();
    led4__init();
}

static void application__start(void) {
//    wdt__reset();
//    wdt__prescaler_set(WDTO_2S);
//    wdt__enable_interrupt();
    sei();
}

ISR(WDT_vect) {
    wdt__disable_interrupt();
    led1__toggle();
}


// =============================================================================
// Entry point.
// =============================================================================

int main(void) {
    application__init();
    application__start();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        uint8_t state = IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN));
        if (!(state & _BV(IN__BUTTON1__PIN))) {
            wdt__reset();
            wdt__prescaler_set(WDTO_500MS);
            wdt__enable_interrupt();
        }
        if (!(state & _BV(IN__BUTTON2__PIN))) {
            wdt__reset();
            wdt__prescaler_set(WDTO_1S);
            wdt__enable_interrupt();
        }
        if (!(state & _BV(IN__BUTTON3__PIN))) {
            wdt__reset();
            wdt__prescaler_set(WDTO_2S);
            wdt__enable_interrupt();
        }
        if (!(state & _BV(IN__BUTTON4__PIN))) {
            wdt__reset();
            wdt__prescaler_set(WDTO_4S);
            wdt__enable_interrupt();
        }

        _delay_ms(200);
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
