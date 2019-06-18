#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_d__encoders.h"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.h"
#include <cpu/avr/asm.h>
#include <avr/interrupt.h>


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1


void keyboard__port_d__encoders__process_encoder(uint8_t state, uint8_t changes, uint8_t encoder) {
    uint8_t pin_a = keyboard__pins__port_d__pin_a_for_encoder(encoder);
    uint8_t pin_b = keyboard__pins__port_d__pin_b_for_encoder(encoder);

    if (changes & ((uint8_t) (1U << pin_a))) {
        // Changed value of pin A: 00->10, 10->00, 11->01, 01->11
        keyboard__port_d__mask__clear_bit(pin_a);
        keyboard__port_d__previous_state__copy_bit(state, pin_a);

        if (state & ((uint8_t) (1U << pin_a))) {
            // new A is 1: was 00->10 [-1 if B is 0] or 01->11 [+1 if B is 1]
            keyboard__encoders__increment_if_bit_set(encoder, state, pin_b);
        } else {
            // new A is 0: was 10->00 [+1 if B is 0] or 11->01 [-1 if B is 1]
            keyboard__encoders__decrement_if_bit_set(encoder, state, pin_b);
        }
    }

    if (changes & ((uint8_t) (1U << pin_b))) {
        // Changed value of pin B: 00->01, 01->00, 11->10, 10->11
        keyboard__port_d__mask__clear_bit(pin_b);
        keyboard__port_d__previous_state__copy_bit(state, pin_b);

        if (state & ((uint8_t) (1U << pin_b))) {
            // new B is 1: was 00->01 [+1 if A is 0] or 10->11 [-1 if A is 1]
            keyboard__encoders__decrement_if_bit_set(encoder, state, pin_a);
        } else {
            // new B is 0: was 01->00 [-1 if A is 0] or 11->10 [+1 if A is 1]
            keyboard__encoders__increment_if_bit_set(encoder, state, pin_a);
        }
    }
}


void keyboard__port_d__encoders__process(uint8_t state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_d__encoders__process:");
    keyboard__port_d__encoders__process_encoder(state, changes, 3);
    keyboard__port_d__encoders__process_encoder(state, changes, 2);
    keyboard__port_d__encoders__process_encoder(state, changes, 1);
    keyboard__port_d__encoders__process_encoder(state, changes, 0);
}

#endif
