#include <stdbool.h>
#include <services/tx_ring_buffer.h>
#include <cpu/avr/asm.h>
#include "keyboard__interrupts.h"
#include "cpu/avr/pin_change_int0.h"
#include "cpu/avr/pin_change_int1.h"
#include "cpu/avr/pin_change_int2.h"
#include "cpu/avr/gpio.h" // make macros.h


uint8_t keyboard__port_b__previous_state = 0xFF;
uint8_t keyboard__port_c__previous_state = 0xFF;
uint8_t keyboard__port_d__previous_state = 0xFF;


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


/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t keyboard__port_b__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    if (button == 0) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    if (button == 1) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    if (button == 2) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    if (button == 3) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    if (button == 4) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    if (button == 5) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    if (button == 6) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    if (button == 7) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    if (button == 8) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    if (button == 9) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    if (button == 10) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    if (button == 11) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    if (button == 12) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    if (button == 13) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    if (button == 14) return IN__BUTTON15__PIN;
#endif
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xB
    if (button == 15) return IN__BUTTON16__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__port_b__mask(void) {
    // Pin Change Interrupt 0 serves PB0..PB7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xB
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


void keyboard__port_b__init(void) {
    pin_change_int0__mask__set(keyboard__port_b__mask());
}


/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t keyboard__port_c__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xC
    if (button == 0) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xC
    if (button == 1) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xC
    if (button == 2) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xC
    if (button == 3) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xC
    if (button == 4) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xC
    if (button == 5) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xC
    if (button == 6) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xC
    if (button == 7) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xC
    if (button == 8) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xC
    if (button == 9) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xC
    if (button == 10) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xC
    if (button == 11) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xC
    if (button == 12) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xC
    if (button == 13) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xC
    if (button == 14) return IN__BUTTON15__PIN;
#endif
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xC
    if (button == 15) return IN__BUTTON16__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__port_c__mask(void) {
    // Pin Change Interrupt 1 serves PC0..PC6
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xC
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xC
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xC
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xC
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xC
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xC
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xC
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xC
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xC
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xC
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xC
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xC
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xC
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xC
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xC
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xC
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


void keyboard__port_c__init(void) {
    pin_change_int1__mask__set(keyboard__port_c__mask());
}


/**
 * Provides pin number for the given button (if it pertains to port D)
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t keyboard__port_d__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON1__PORT)==0xD
    if (button == 0) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xD
    if (button == 1) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xD
    if (button == 2) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xD
    if (button == 3) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xD
    if (button == 4) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xD
    if (button == 5) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xD
    if (button == 6) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xD
    if (button == 7) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xD
    if (button == 8) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xD
    if (button == 9) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xD
    if (button == 10) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xD
    if (button == 11) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xD
    if (button == 12) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xD
    if (button == 13) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xD
    if (button == 14) return IN__BUTTON15__PIN;
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xD
    if (button == 15) return IN__BUTTON16__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__port_d__mask(void) {
    // Pin Change Interrupt 1 serves PD0..PD7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xD
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xD
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xD
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xD
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xD
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xD
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xD
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xD
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xD
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xD
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xD
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xD
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xD
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xD
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xD
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xD
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}

void keyboard__port_d__init(void) {
    pin_change_int2__mask__set(keyboard__port_d__mask());
}


inline void keyboard__port_b__check_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_b__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_b__on_change(void) {
    uint8_t keyboard__port_b__state = PINB;
    uint8_t keyboard__port_b__changes = keyboard__port_b__state ^ keyboard__port_b__previous_state;

    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 15, 'P', 'p');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 14, 'O', 'o');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 13, 'N', 'n');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 12, 'M', 'm');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 11, 'L', 'l');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 10, 'K', 'k');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 9, 'J', 'j');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 8, 'I', 'i');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 7, 'H', 'h');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 6, 'G', 'g');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 5, 'F', 'f');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 4, 'E', 'e');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 3, 'D', 'd');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 2, 'C', 'c');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 1, 'B', 'b');
    keyboard__port_b__check_button(keyboard__port_b__state, keyboard__port_b__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_b__on_change__done:");
    keyboard__port_b__previous_state = keyboard__port_b__state;
}


inline void keyboard__port_c__check_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_c__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_c__on_change(void) {
    uint8_t keyboard__port_c__state = PINC;
    uint8_t keyboard__port_c__changes = keyboard__port_c__state ^ keyboard__port_c__previous_state;

    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 15, 'P', 'p');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 14, 'O', 'o');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 13, 'N', 'n');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 12, 'M', 'm');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 11, 'L', 'l');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 10, 'K', 'k');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 9, 'J', 'j');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 8, 'I', 'i');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 7, 'H', 'h');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 6, 'G', 'g');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 5, 'F', 'f');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 4, 'E', 'e');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 3, 'D', 'd');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 2, 'C', 'c');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 1, 'B', 'b');
    keyboard__port_c__check_button(keyboard__port_c__state, keyboard__port_c__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_c__on_change__done:");
    keyboard__port_c__previous_state = keyboard__port_c__state;
}


inline void keyboard__port_d__check_button(
    uint8_t state, uint8_t changes, uint8_t button, uint8_t pressed_code, uint8_t released_code)
{
    keyboard__interrupts__process_pin(
        keyboard__port_d__pin_for_button(button), state, changes, pressed_code, released_code
    );
}


void keyboard__port_d__on_change(void) {
    uint8_t keyboard__port_d__state = PIND;
    uint8_t keyboard__port_d__changes = keyboard__port_d__state ^ keyboard__port_d__previous_state;

    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 15, 'P', 'p');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 14, 'O', 'o');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 13, 'N', 'n');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 12, 'M', 'm');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 11, 'L', 'l');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 10, 'K', 'k');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 9, 'J', 'j');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 8, 'I', 'i');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 7, 'H', 'h');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 6, 'G', 'g');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 5, 'F', 'f');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 4, 'E', 'e');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 3, 'D', 'd');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 2, 'C', 'c');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 1, 'B', 'b');
    keyboard__port_d__check_button(keyboard__port_d__state, keyboard__port_d__changes, 0, 'A', 'a');

    __asm__ __volatile__("keyboard__port_d__on_change__done:");
    keyboard__port_d__previous_state = keyboard__port_d__state;
}


void keyboard__interrupts__init(void) {
    keyboard__port_b__init();
    keyboard__port_c__init();
    keyboard__port_d__init();
}

void keyboard__interrupts__start(void) {
    pin_change_int0__start();
    pin_change_int1__start();
    pin_change_int2__start();
}
