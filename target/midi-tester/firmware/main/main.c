// =============================================================================
// MIDI tester.
// Scans 4 buttons and sends MIDI messages (using Soft USART)
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/services/keyboard/keyboard.h>

#include "soft_usart__timer.h"
#include "soft_usart__tx__thread.h"
#include "soft_usart__tx.h"

void keyboard__port_b__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_b__debounce_timer__init(void) {}
void keyboard__port_b__debounce_timer__start(void) {}
bool keyboard__port_b__debounce_timer__is_started(void) { return false; }


/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-31)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    soft_usart__tx__write('B');
    soft_usart__tx__write('0' + button);
    soft_usart__tx__write('0' + (state & _BV(bit)));
    soft_usart__tx__write(' ');
    return true;
}


int main(void) {
    soft_usart__tx__pin__init();
    soft_usart__timer__init();
    keyboard__init();

    sei();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
//    for(;;) {
//        soft_usart__tx__write('H');
//        soft_usart__tx__write('e');
//        soft_usart__tx__write('l');
//        soft_usart__tx__write('l');
//        soft_usart__tx__write('o');
//
//        _delay_ms(500);
//    }
    for(;;) {
        keyboard__run();
    }

#pragma clang diagnostic pop

    return 0;
}
