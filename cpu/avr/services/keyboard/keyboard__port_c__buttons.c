#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.h"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.h"
#include <cpu/avr/asm.h>


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

inline void keyboard__port_c__buttons__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_c__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        if (keyboard__handle_button_event(button, state, pin)) {
            keyboard__port_c__mask__clear_bit(pin);
//            keyboard__port_c__previous_state__copy_bit(state, pin);
        }
    }
}


void keyboard__port_c__buttons__process(uint8_t state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__31:");
    keyboard__port_c__buttons__process_button(state, changes, 31);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__30:");
    keyboard__port_c__buttons__process_button(state, changes, 30);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__29:");
    keyboard__port_c__buttons__process_button(state, changes, 29);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__28:");
    keyboard__port_c__buttons__process_button(state, changes, 28);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__27:");
    keyboard__port_c__buttons__process_button(state, changes, 27);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__26:");
    keyboard__port_c__buttons__process_button(state, changes, 26);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__25:");
    keyboard__port_c__buttons__process_button(state, changes, 25);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__24:");
    keyboard__port_c__buttons__process_button(state, changes, 24);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__23:");
    keyboard__port_c__buttons__process_button(state, changes, 23);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__22:");
    keyboard__port_c__buttons__process_button(state, changes, 22);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__21:");
    keyboard__port_c__buttons__process_button(state, changes, 21);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__20:");
    keyboard__port_c__buttons__process_button(state, changes, 20);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__19:");
    keyboard__port_c__buttons__process_button(state, changes, 19);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__18:");
    keyboard__port_c__buttons__process_button(state, changes, 18);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__17:");
    keyboard__port_c__buttons__process_button(state, changes, 17);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__16:");
    keyboard__port_c__buttons__process_button(state, changes, 16);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__15:");
    keyboard__port_c__buttons__process_button(state, changes, 15);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__14:");
    keyboard__port_c__buttons__process_button(state, changes, 14);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__13:");
    keyboard__port_c__buttons__process_button(state, changes, 13);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__12:");
    keyboard__port_c__buttons__process_button(state, changes, 12);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__11:");
    keyboard__port_c__buttons__process_button(state, changes, 11);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__10:");
    keyboard__port_c__buttons__process_button(state, changes, 10);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__9:");
    keyboard__port_c__buttons__process_button(state, changes, 9);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__8:");
    keyboard__port_c__buttons__process_button(state, changes, 8);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__7:");
    keyboard__port_c__buttons__process_button(state, changes, 7);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__6:");
    keyboard__port_c__buttons__process_button(state, changes, 6);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__5:");
    keyboard__port_c__buttons__process_button(state, changes, 5);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__4:");
    keyboard__port_c__buttons__process_button(state, changes, 4);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__3:");
    keyboard__port_c__buttons__process_button(state, changes, 3);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__2:");
    keyboard__port_c__buttons__process_button(state, changes, 2);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__1:");
    keyboard__port_c__buttons__process_button(state, changes, 1);
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__0:");
    keyboard__port_c__buttons__process_button(state, changes, 0);
}

#endif
