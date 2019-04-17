// =============================================================================
// Test: report pin change interrupts to USART via ring buffer
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <drivers/keyboard__pins.h>

#include "led1.h"
#include "led2.h"
#include "led3.h"

#include "cpu/avr/usart0__tx_polled.h"

#include "keyboard.h"


// =============================================================================
// Handlers
// =============================================================================

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline void keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
//    uint8_t code;
//    IF_BIT_SET_LOAD_A_ELSE_B(code, state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
//    if (state & ((uint8_t)(1 << bit))) {
//        code = (uint8_t)'A' + button;
//    } else {
//        code = (uint8_t)'a' + button;
//    }
//    (void)state;
    usart0__putc(code);
}


// =============================================================================
// Application
// =============================================================================


void application__init(void) {
    keyboard__init();

    led1__init();
    led2__init();
    led3__init();

    usart0__init();
    usart0__tx__enabled__set(1);
}


void application__start(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_ms(10);
    application__start();


#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    led1__toggle();
    usart0__out__write('!');

    uint8_t previous_state = 0xFF;
    for(;;) {
//        keyboard__run();

        uint8_t keyboard__port_c__state = PINC;
        uint8_t changes = ((uint8_t)0x0F) & (keyboard__port_c__state ^ previous_state);
        if (changes) {
//            uint8_t pin = keyboard__pins__port_c__pin_for_button(8);
            uint8_t pin = 3;
            if (changes & ((uint8_t) (1 << pin))) {
//                COPY_BIT(keyboard__port_c__state, pin, previous_state, pin);
                previous_state ^= ((uint8_t) (1 << pin));
                keyboard__handle_button_event(8, keyboard__port_c__state, pin);
            }
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
