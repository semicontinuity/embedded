#include <services/tx_ring_buffer.h>

#include "drivers/keyboard__debounce_timer.h"
#include "keyboard__interrupts.h"
#include "keyboard__pins.h"

#include "cpu/avr/pin_change_int0.h"
#include "cpu/avr/pin_change_int1.h"
#include "cpu/avr/pin_change_int2.h"


#ifdef KEYBOARD__PORT_B__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_b__previous_state asm(QUOTE(KEYBOARD__PORT_B__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_b__previous_state;
#endif

#ifdef KEYBOARD__PORT_C__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_c__previous_state asm(QUOTE(KEYBOARD__PORT_C__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_c__previous_state;
#endif

#ifdef KEYBOARD__PORT_D__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_d__previous_state asm(QUOTE(KEYBOARD__PORT_D__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_d__previous_state;
#endif


#ifdef KEYBOARD__PORT_B__CHANGES__REG
register volatile uint8_t keyboard__port_b__changes asm(QUOTE(KEYBOARD__PORT_B__CHANGES__REG));
#else
volatile uint8_t keyboard__port_b__changes;
#endif

#ifdef KEYBOARD__PORT_C__CHANGES__REG
register volatile uint8_t keyboard__port_c__changes asm(QUOTE(KEYBOARD__PORT_C__CHANGES__REG));
#else
volatile uint8_t keyboard__port_c__changes;
#endif

#ifdef KEYBOARD__PORT_D__CHANGES__REG
register volatile uint8_t keyboard__port_d__changes asm(QUOTE(KEYBOARD__PORT_D__CHANGES__REG));
#else
volatile uint8_t keyboard__port_d__changes;
#endif


void keyboard__init(void) {
    keyboard__port_b__previous_state = 0xFF;
    keyboard__port_c__previous_state = 0xFF;
    keyboard__port_d__previous_state = 0xFF;
    pin_change_int0__mask__set(keyboard__pins__port_b__button_pins_mask());
    pin_change_int1__mask__set(keyboard__pins__port_c__button_pins_mask());
    pin_change_int2__mask__set(keyboard__pins__port_d__button_pins_mask());
}

void keyboard__start(void) {
    pin_change_int0__start();
    pin_change_int1__start();
    pin_change_int2__start();
}

/**
 * The callback called when the debounce timer has expired.
 */
void keyboard__debounce_timer__run(void) {
    keyboard__init();   // just re-enable all pin change interrupts
}



inline void keyboard__port_b__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_b__pin_for_button(button);
    if (changes & ((uint8_t) (1 << pin))) {
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_b__on_change(void) {
    uint8_t keyboard__port_b__state = PINB;
#ifndef KEYBOARD__PORT_B__CHANGES__REG
    uint8_t keyboard__port_b__changes;
#endif
    uint8_t mask = pin_change_int0__mask__get();
    keyboard__port_b__changes = mask & (keyboard__port_b__state ^ keyboard__port_b__previous_state);
    pin_change_int0__mask__set(mask ^ keyboard__port_b__changes);
    keyboard__port_b__previous_state = keyboard__port_b__state;
    keyboard__debounce_timer__start();

    __asm__ __volatile__("keyboard__port_b__process_button__15:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 15);
    __asm__ __volatile__("keyboard__port_b__process_button__14:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 14);
    __asm__ __volatile__("keyboard__port_b__process_button__13:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 13);
    __asm__ __volatile__("keyboard__port_b__process_button__12:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 12);
    __asm__ __volatile__("keyboard__port_b__process_button__11:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 11);
    __asm__ __volatile__("keyboard__port_b__process_button__10:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 10);
    __asm__ __volatile__("keyboard__port_b__process_button__9:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 9);
    __asm__ __volatile__("keyboard__port_b__process_button__8:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 8);
    __asm__ __volatile__("keyboard__port_b__process_button__7:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 7);
    __asm__ __volatile__("keyboard__port_b__process_button__6:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 6);
    __asm__ __volatile__("keyboard__port_b__process_button__5:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 5);
    __asm__ __volatile__("keyboard__port_b__process_button__4:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 4);
    __asm__ __volatile__("keyboard__port_b__process_button__3:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 3);
    __asm__ __volatile__("keyboard__port_b__process_button__2:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 2);
    __asm__ __volatile__("keyboard__port_b__process_button__1:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 1);
    __asm__ __volatile__("keyboard__port_b__process_button__0:");
    keyboard__port_b__process_button(keyboard__port_b__state, keyboard__port_b__changes, 0);

    __asm__ __volatile__("keyboard__port_b__on_change__done:");
}



inline void keyboard__port_c__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_c__pin_for_button(button);
    if (changes & ((uint8_t) (1 << pin))) {
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_c__on_change(void) {
    uint8_t keyboard__port_c__state = PINC;
#ifndef KEYBOARD__PORT_C__CHANGES__REG
    uint8_t keyboard__port_c__changes;
#endif
    uint8_t mask = pin_change_int1__mask__get();
    keyboard__port_c__changes = mask & (keyboard__port_c__state ^ keyboard__port_c__previous_state);
    pin_change_int1__mask__set(mask ^ keyboard__port_c__changes);
    keyboard__port_c__previous_state = keyboard__port_c__state;
    keyboard__debounce_timer__start();

    __asm__ __volatile__("keyboard__port_c__process_button__15:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 15);
    __asm__ __volatile__("keyboard__port_c__process_button__14:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 14);
    __asm__ __volatile__("keyboard__port_c__process_button__13:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 13);
    __asm__ __volatile__("keyboard__port_c__process_button__12:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 12);
    __asm__ __volatile__("keyboard__port_c__process_button__11:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 11);
    __asm__ __volatile__("keyboard__port_c__process_button__10:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 10);
    __asm__ __volatile__("keyboard__port_c__process_button__9:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 9);
    __asm__ __volatile__("keyboard__port_c__process_button__8:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 8);
    __asm__ __volatile__("keyboard__port_c__process_button__7:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 7);
    __asm__ __volatile__("keyboard__port_c__process_button__6:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 6);
    __asm__ __volatile__("keyboard__port_c__process_button__5:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 5);
    __asm__ __volatile__("keyboard__port_c__process_button__4:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 4);
    __asm__ __volatile__("keyboard__port_c__process_button__3:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 3);
    __asm__ __volatile__("keyboard__port_c__process_button__2:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 2);
    __asm__ __volatile__("keyboard__port_c__process_button__1:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 1);
    __asm__ __volatile__("keyboard__port_c__process_button__0:");
    keyboard__port_c__process_button(keyboard__port_c__state, keyboard__port_c__changes, 0);

    __asm__ __volatile__("keyboard__port_c__on_change__done:");
}



inline void keyboard__port_d__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_d__pin_for_button(button);
    if (changes & ((uint8_t) (1 << pin))) {
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_d__on_change(void) {
    uint8_t keyboard__port_d__state = PIND;
#ifndef KEYBOARD__PORT_D__CHANGES__REG
    uint8_t keyboard__port_d__changes;
#endif
    uint8_t mask = pin_change_int2__mask__get();
    keyboard__port_d__changes = mask & (keyboard__port_d__state ^ keyboard__port_d__previous_state);
    pin_change_int2__mask__set(mask ^ keyboard__port_d__changes);
    keyboard__port_d__previous_state = keyboard__port_d__state;
    keyboard__debounce_timer__start();

    __asm__ __volatile__("keyboard__port_d__process_button__15:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 15);
    __asm__ __volatile__("keyboard__port_d__process_button__14:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 14);
    __asm__ __volatile__("keyboard__port_d__process_button__13:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 13);
    __asm__ __volatile__("keyboard__port_d__process_button__12:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 12);
    __asm__ __volatile__("keyboard__port_d__process_button__11:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 11);
    __asm__ __volatile__("keyboard__port_d__process_button__10:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 10);
    __asm__ __volatile__("keyboard__port_d__process_button__9:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 9);
    __asm__ __volatile__("keyboard__port_d__process_button__8:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 8);
    __asm__ __volatile__("keyboard__port_d__process_button__7:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 7);
    __asm__ __volatile__("keyboard__port_d__process_button__6:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 6);
    __asm__ __volatile__("keyboard__port_d__process_button__5:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 5);
    __asm__ __volatile__("keyboard__port_d__process_button__4:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 4);
    __asm__ __volatile__("keyboard__port_d__process_button__3:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 3);
    __asm__ __volatile__("keyboard__port_d__process_button__2:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 2);
    __asm__ __volatile__("keyboard__port_d__process_button__1:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 1);
    __asm__ __volatile__("keyboard__port_d__process_button__0:");
    keyboard__port_d__process_button(keyboard__port_d__state, keyboard__port_d__changes, 0);

    __asm__ __volatile__("keyboard__port_d__on_change__done:");
}
