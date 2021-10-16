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


inline void keyboard__port_c__buttons__process(uint8_t state, uint8_t changes) {
    #if defined(IN__BUTTON31__PORT) && defined(IN__BUTTON31__PIN) && SINGLEQUOTED(IN__BUTTON31__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__31:");
    keyboard__port_c__buttons__process_button(state, changes, 31);
    #endif

    #if defined(IN__BUTTON30__PORT) && defined(IN__BUTTON30__PIN) && SINGLEQUOTED(IN__BUTTON30__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__30:");
    keyboard__port_c__buttons__process_button(state, changes, 30);
    #endif

    #if defined(IN__BUTTON29__PORT) && defined(IN__BUTTON29__PIN) && SINGLEQUOTED(IN__BUTTON29__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__29:");
    keyboard__port_c__buttons__process_button(state, changes, 29);
    #endif

    #if defined(IN__BUTTON28__PORT) && defined(IN__BUTTON28__PIN) && SINGLEQUOTED(IN__BUTTON28__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__28:");
    keyboard__port_c__buttons__process_button(state, changes, 28);
    #endif

    #if defined(IN__BUTTON27__PORT) && defined(IN__BUTTON27__PIN) && SINGLEQUOTED(IN__BUTTON27__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__27:");
    keyboard__port_c__buttons__process_button(state, changes, 27);
    #endif

    #if defined(IN__BUTTON26__PORT) && defined(IN__BUTTON26__PIN) && SINGLEQUOTED(IN__BUTTON26__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__26:");
    keyboard__port_c__buttons__process_button(state, changes, 26);
    #endif

    #if defined(IN__BUTTON25__PORT) && defined(IN__BUTTON25__PIN) && SINGLEQUOTED(IN__BUTTON25__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__25:");
    keyboard__port_c__buttons__process_button(state, changes, 25);
    #endif

    #if defined(IN__BUTTON24__PORT) && defined(IN__BUTTON24__PIN) && SINGLEQUOTED(IN__BUTTON24__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__24:");
    keyboard__port_c__buttons__process_button(state, changes, 24);
    #endif

    #if defined(IN__BUTTON23__PORT) && defined(IN__BUTTON23__PIN) && SINGLEQUOTED(IN__BUTTON23__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__23:");
    keyboard__port_c__buttons__process_button(state, changes, 23);
    #endif

    #if defined(IN__BUTTON22__PORT) && defined(IN__BUTTON22__PIN) && SINGLEQUOTED(IN__BUTTON22__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__22:");
    keyboard__port_c__buttons__process_button(state, changes, 22);
    #endif

    #if defined(IN__BUTTON21__PORT) && defined(IN__BUTTON21__PIN) && SINGLEQUOTED(IN__BUTTON21__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__21:");
    keyboard__port_c__buttons__process_button(state, changes, 21);
    #endif

    #if defined(IN__BUTTON20__PORT) && defined(IN__BUTTON20__PIN) && SINGLEQUOTED(IN__BUTTON20__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__20:");
    keyboard__port_c__buttons__process_button(state, changes, 20);
    #endif

    #if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN) && SINGLEQUOTED(IN__BUTTON19__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__19:");
    keyboard__port_c__buttons__process_button(state, changes, 19);
    #endif

    #if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN) && SINGLEQUOTED(IN__BUTTON18__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__18:");
    keyboard__port_c__buttons__process_button(state, changes, 18);
    #endif

    #if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN) && SINGLEQUOTED(IN__BUTTON17__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__17:");
    keyboard__port_c__buttons__process_button(state, changes, 17);
    #endif

    #if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN) && SINGLEQUOTED(IN__BUTTON16__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__16:");
    keyboard__port_c__buttons__process_button(state, changes, 16);
    #endif

    #if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN) && SINGLEQUOTED(IN__BUTTON15__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__15:");
    keyboard__port_c__buttons__process_button(state, changes, 15);
    #endif

    #if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN) && SINGLEQUOTED(IN__BUTTON14__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__14:");
    keyboard__port_c__buttons__process_button(state, changes, 14);
    #endif

    #if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN) && SINGLEQUOTED(IN__BUTTON13__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__13:");
    keyboard__port_c__buttons__process_button(state, changes, 13);
    #endif

    #if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN) && SINGLEQUOTED(IN__BUTTON12__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__12:");
    keyboard__port_c__buttons__process_button(state, changes, 12);
    #endif

    #if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN) && SINGLEQUOTED(IN__BUTTON11__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__11:");
    keyboard__port_c__buttons__process_button(state, changes, 11);
    #endif

    #if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN) && SINGLEQUOTED(IN__BUTTON10__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__10:");
    keyboard__port_c__buttons__process_button(state, changes, 10);
    #endif

    #if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN) && SINGLEQUOTED(IN__BUTTON9__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__9:");
    keyboard__port_c__buttons__process_button(state, changes, 9);
    #endif

    #if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN) && SINGLEQUOTED(IN__BUTTON8__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__8:");
    keyboard__port_c__buttons__process_button(state, changes, 8);
    #endif

    #if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN) && SINGLEQUOTED(IN__BUTTON7__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__7:");
    keyboard__port_c__buttons__process_button(state, changes, 7);
    #endif

    #if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN) && SINGLEQUOTED(IN__BUTTON6__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__6:");
    keyboard__port_c__buttons__process_button(state, changes, 6);
    #endif

    #if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN) && SINGLEQUOTED(IN__BUTTON5__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__5:");
    keyboard__port_c__buttons__process_button(state, changes, 5);
    #endif

    #if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN) && SINGLEQUOTED(IN__BUTTON4__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__4:");
    keyboard__port_c__buttons__process_button(state, changes, 4);
    #endif

    #if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN) && SINGLEQUOTED(IN__BUTTON3__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__3:");
    keyboard__port_c__buttons__process_button(state, changes, 3);
    #endif

    #if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN) && SINGLEQUOTED(IN__BUTTON2__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__2:");
    keyboard__port_c__buttons__process_button(state, changes, 2);
    #endif

    #if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN) && SINGLEQUOTED(IN__BUTTON1__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__1:");
    keyboard__port_c__buttons__process_button(state, changes, 1);
    #endif

    #if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN) && SINGLEQUOTED(IN__BUTTON0__PORT) == 'C'
    __asm__ __volatile__("keyboard__port_c__buttons__process_button__0:");
    keyboard__port_c__buttons__process_button(state, changes, 0);
    #endif
}

#endif
