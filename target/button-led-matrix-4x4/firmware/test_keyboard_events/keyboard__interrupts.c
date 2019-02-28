#include <stdbool.h>
#include <services/tx_ring_buffer.h>
#include <cpu/avr/asm.h>
#include "keyboard__interrupts.h"
#include "keyboard__pins.h"
#include "cpu/avr/pin_change_int0.h"
#include "cpu/avr/pin_change_int1.h"
#include "cpu/avr/pin_change_int2.h"


uint8_t keyboard__port_b__previous_state = 0xFF;
uint8_t keyboard__port_c__previous_state = 0xFF;
uint8_t keyboard__port_d__previous_state = 0xFF;


void keyboard__interrupts__init(void) {
    pin_change_int0__mask__set(keyboard__port_b__button_pins_mask());
    pin_change_int1__mask__set(keyboard__port_c__button_pins_mask());
    pin_change_int2__mask__set(keyboard__port_d__button_pins_mask());
}

void keyboard__interrupts__start(void) {
    pin_change_int0__start();
    pin_change_int1__start();
    pin_change_int2__start();
}



inline void keyboard__interrupts__process_pin(
    uint8_t pin, uint8_t state, uint8_t changes, uint8_t pressed_code, uint8_t released_code)
{
    if (changes & ((uint8_t)(1 << pin))) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, pin, released_code, pressed_code);
        if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
            tx_ring_buffer__put(code);
        }
    }
}



inline void keyboard__port_b__process_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_b__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_b__on_change(void) {
    uint8_t keyboard__port_b__state = PINB;
    uint8_t keyboard__port_b__changes = keyboard__port_b__state ^ keyboard__port_b__previous_state;

    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 15, 'P', 'p');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 14, 'O', 'o');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 13, 'N', 'n');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 12, 'M', 'm');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 11, 'L', 'l');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 10, 'K', 'k');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 9, 'J', 'j');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 8, 'I', 'i');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 7, 'H', 'h');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 6, 'G', 'g');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 5, 'F', 'f');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 4, 'E', 'e');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 3, 'D', 'd');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 2, 'C', 'c');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 1, 'B', 'b');
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_b__on_change__done:");
    keyboard__port_b__previous_state = keyboard__port_b__state;
}



inline void keyboard__port_c__process_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_c__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_c__on_change(void) {
    uint8_t keyboard__port_c__state = PINC;
    uint8_t keyboard__port_c__changes = keyboard__port_c__state ^ keyboard__port_c__previous_state;

    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 15, 'P', 'p');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 14, 'O', 'o');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 13, 'N', 'n');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 12, 'M', 'm');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 11, 'L', 'l');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 10, 'K', 'k');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 9, 'J', 'j');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 8, 'I', 'i');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 7, 'H', 'h');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 6, 'G', 'g');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 5, 'F', 'f');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 4, 'E', 'e');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 3, 'D', 'd');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 2, 'C', 'c');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 1, 'B', 'b');
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_c__on_change__done:");
    keyboard__port_c__previous_state = keyboard__port_c__state;
}



inline void keyboard__port_d__process_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_d__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_d__on_change(void) {
    uint8_t keyboard__port_d__state = PIND;
    uint8_t keyboard__port_d__changes = keyboard__port_d__state ^ keyboard__port_d__previous_state;

    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 15, 'P', 'p');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 14, 'O', 'o');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 13, 'N', 'n');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 12, 'M', 'm');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 11, 'L', 'l');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 10, 'K', 'k');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 9, 'J', 'j');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 8, 'I', 'i');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 7, 'H', 'h');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 6, 'G', 'g');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 5, 'F', 'f');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 4, 'E', 'e');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 3, 'D', 'd');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 2, 'C', 'c');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 1, 'B', 'b');
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_d__on_change__done:");
    keyboard__port_d__previous_state = keyboard__port_d__state;
}
