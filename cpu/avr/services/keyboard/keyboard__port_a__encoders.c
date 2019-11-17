#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_a__encoders.h"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.h"


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1


void keyboard__port_a__encoders__process_encoder(const uint8_t state, const uint8_t changes, const uint8_t encoder) {
    const uint8_t pin_a = keyboard__pins__port_a__pin_a_for_encoder(encoder);
    const uint8_t pin_a_mask = (uint8_t) (1U << pin_a);
    const uint8_t pin_b = keyboard__pins__port_a__pin_b_for_encoder(encoder);
    const uint8_t pin_b_mask = (uint8_t) (1U << pin_b);

    if (changes & pin_a_mask) {
        __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__a:");
        // Changed value of pin A: 00->10, 10->00, 11->01, 01->11

        if (state & pin_a_mask) {
            // new A is 1: was 00->10 [-1 if B is 0] or 01->11 [+1 if B is 1]
            __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__a_0_1:");
            keyboard__encoders__increment_if_bit_set(encoder, state, pin_b);
        } else {
            // new A is 0: was 10->00 [+1 if B is 0] or 11->01 [-1 if B is 1]
            __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__a_1_0:");
            keyboard__encoders__decrement_if_bit_set(encoder, state, pin_b);
        }

        keyboard__port_a__mask__clear_bit(pin_a); // mark as being debounced
    }
    else if (changes & pin_b_mask) {    // "else" produces extra jump, but makes compiler use the same reg for 'state'
        __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__b:");
        // Changed value of pin B: 00->01, 01->00, 11->10, 10->11

        if (state & pin_b_mask) {
            // new B is 1: was 00->01 [+1 if A is 0] or 10->11 [-1 if A is 1]
            __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__b_0_1:");
            keyboard__encoders__decrement_if_bit_set(encoder, state, pin_a);
        } else {
            // new B is 0: was 01->00 [-1 if A is 0] or 11->10 [+1 if A is 1]
            __asm__ __volatile__("keyboard__port_a__encoders__process_encoder__b_1_0:");
            keyboard__encoders__increment_if_bit_set(encoder, state, pin_a);
        }

        keyboard__port_a__mask__clear_bit(pin_b); // mark as being debounced
    }
}


void keyboard__port_a__encoders__process(uint8_t state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_a__encoders__process:");
    keyboard__port_a__encoders__process_encoder(state, changes, 3);
    keyboard__port_a__encoders__process_encoder(state, changes, 2);
    keyboard__port_a__encoders__process_encoder(state, changes, 1);
    keyboard__port_a__encoders__process_encoder(state, changes, 0);
}

#endif
