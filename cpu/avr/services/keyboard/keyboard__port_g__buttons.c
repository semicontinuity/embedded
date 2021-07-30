#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_g__buttons.h"
#include <cpu/avr/asm.h>


#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1

inline void keyboard__port_g__buttons__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_g__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        if (keyboard__handle_button_event(button, state, pin)) {
            keyboard__port_g__mask__clear_bit(pin);
//            keyboard__port_g__previous_state__copy_bit(state, pin);
        }
    }
}


inline void keyboard__port_g__buttons__process(uint8_t state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__63:");
    keyboard__port_g__buttons__process_button(state, changes, 63);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__62:");
    keyboard__port_g__buttons__process_button(state, changes, 62);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__61:");
    keyboard__port_g__buttons__process_button(state, changes, 61);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__60:");
    keyboard__port_g__buttons__process_button(state, changes, 60);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__59:");
    keyboard__port_g__buttons__process_button(state, changes, 59);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__58:");
    keyboard__port_g__buttons__process_button(state, changes, 58);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__57:");
    keyboard__port_g__buttons__process_button(state, changes, 57);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__56:");
    keyboard__port_g__buttons__process_button(state, changes, 56);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__55:");
    keyboard__port_g__buttons__process_button(state, changes, 55);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__54:");
    keyboard__port_g__buttons__process_button(state, changes, 54);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__53:");
    keyboard__port_g__buttons__process_button(state, changes, 53);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__52:");
    keyboard__port_g__buttons__process_button(state, changes, 52);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__51:");
    keyboard__port_g__buttons__process_button(state, changes, 51);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__50:");
    keyboard__port_g__buttons__process_button(state, changes, 50);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__49:");
    keyboard__port_g__buttons__process_button(state, changes, 49);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__48:");
    keyboard__port_g__buttons__process_button(state, changes, 48);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__47:");
    keyboard__port_g__buttons__process_button(state, changes, 47);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__46:");
    keyboard__port_g__buttons__process_button(state, changes, 46);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__45:");
    keyboard__port_g__buttons__process_button(state, changes, 45);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__44:");
    keyboard__port_g__buttons__process_button(state, changes, 44);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__43:");
    keyboard__port_g__buttons__process_button(state, changes, 43);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__42:");
    keyboard__port_g__buttons__process_button(state, changes, 42);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__41:");
    keyboard__port_g__buttons__process_button(state, changes, 41);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__40:");
    keyboard__port_g__buttons__process_button(state, changes, 40);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__39:");
    keyboard__port_g__buttons__process_button(state, changes, 39);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__38:");
    keyboard__port_g__buttons__process_button(state, changes, 38);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__37:");
    keyboard__port_g__buttons__process_button(state, changes, 37);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__36:");
    keyboard__port_g__buttons__process_button(state, changes, 36);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__35:");
    keyboard__port_g__buttons__process_button(state, changes, 35);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__34:");
    keyboard__port_g__buttons__process_button(state, changes, 34);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__33:");
    keyboard__port_g__buttons__process_button(state, changes, 33);
    __asm__ __volatile__("keyboard__port_g__buttons__process_button__32:");
    keyboard__port_g__buttons__process_button(state, changes, 32);
}

#endif
