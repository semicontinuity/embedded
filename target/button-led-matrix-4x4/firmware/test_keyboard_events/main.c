// =============================================================================
// Test: report pin change interrupts to USART via ring buffer
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include "led1.h"
#include "led2.h"
#include "led3.h"

#include "services/tx_ring_buffer.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__tx.h"

#include "keyboard__pins.h"
#include "keyboard__interrupts.h"
#include "drivers/keyboard__debounce_timer.h"


// =============================================================================
// Handlers
// =============================================================================

bool comm__tx__has_next(void) {
    return true; // interrupt triggered only if TX buffer is not empty
}

uint8_t comm__tx__next() {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {
    // never invoked
}

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline void keyboard__interrupts__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    keyboard__debounce_timer__start();
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
    }
}

/**
 * The callback called when the debounce timer has expired.
 */
void keyboard__debounce_timer__run(void) {
    led1__toggle();
    keyboard__interrupts__init();
}

// =============================================================================
// Application
// =============================================================================


void application__init(void) {
    keyboard__pins__init();

    led1__init();
    led2__init();
    led3__init();

    usart0__init();

    keyboard__debounce_timer__init();
    keyboard__interrupts__init();
}


void application__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
    keyboard__interrupts__start();
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
