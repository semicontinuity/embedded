#include <services/tx_ring_buffer.h>
#include <cpu/avr/asm.h>

#include "drivers/keyboard__pins.h"
#include "drivers/keyboard__debounce_timer.h"
#include "keyboard.h"


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_a__previous_state asm(QUOTE(KEYBOARD__PORT_A__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_a__previous_state;
#endif

#ifdef KEYBOARD__PORT_A__MASK__REG
register volatile uint8_t keyboard__port_a__mask asm(QUOTE(KEYBOARD__PORT_A__MASK__REG));
#else
volatile uint8_t keyboard__port_a__mask;
#endif

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#ifdef KEYBOARD__PORT_B__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_b__previous_state asm(QUOTE(KEYBOARD__PORT_B__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_b__previous_state;
#endif

#ifdef KEYBOARD__PORT_B__MASK__REG
register volatile uint8_t keyboard__port_b__mask asm(QUOTE(KEYBOARD__PORT_B__MASK__REG));
#else
volatile uint8_t keyboard__port_b__mask;
#endif

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#ifdef KEYBOARD__PORT_C__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_c__previous_state asm(QUOTE(KEYBOARD__PORT_C__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_c__previous_state;
#endif

#ifdef KEYBOARD__PORT_C__MASK__REG
register volatile uint8_t keyboard__port_c__mask asm(QUOTE(KEYBOARD__PORT_C__MASK__REG));
#else
volatile uint8_t keyboard__port_c__mask;
#endif

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#ifdef KEYBOARD__PORT_D__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_d__previous_state asm(QUOTE(KEYBOARD__PORT_D__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_d__previous_state;
#endif

#ifdef KEYBOARD__PORT_D__MASK__REG
register volatile uint8_t keyboard__port_d__mask asm(QUOTE(KEYBOARD__PORT_D__MASK__REG));
#else
volatile uint8_t keyboard__port_d__mask;
#endif

#endif


inline void keyboard__init_masks(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__mask = keyboard__pins__port_a__button_pins_mask();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__mask = keyboard__pins__port_b__button_pins_mask();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__mask = keyboard__pins__port_c__button_pins_mask();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__mask = keyboard__pins__port_d__button_pins_mask();
#endif
}


inline void keyboard__init_previous_states(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__previous_state = 0xFF;
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__previous_state = 0xFF;
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__previous_state = 0xFF;
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__previous_state = 0xFF;
#endif
}

void keyboard__init(void) {
    keyboard__pins__init();
    keyboard__debounce_timer__init();
    keyboard__init_previous_states();
    keyboard__init_masks();
}


/**
 * The callback called when the debounce timer has expired.
 */
void keyboard__debounce_timer__run(void) {
    keyboard__init_masks();
}


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

inline void keyboard__port_a__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_a__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        keyboard__port_a__mask &= (uint8_t) ~((uint8_t) (1U << pin));
        COPY_BIT(state, pin, keyboard__port_a__previous_state, pin);
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_a__process_events(uint8_t keyboard__port_a__state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_a__process_button__15:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 15);
    __asm__ __volatile__("keyboard__port_a__process_button__14:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 14);
    __asm__ __volatile__("keyboard__port_a__process_button__13:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 13);
    __asm__ __volatile__("keyboard__port_a__process_button__12:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 12);
    __asm__ __volatile__("keyboard__port_a__process_button__11:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 11);
    __asm__ __volatile__("keyboard__port_a__process_button__10:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 10);
    __asm__ __volatile__("keyboard__port_a__process_button__9:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 9);
    __asm__ __volatile__("keyboard__port_a__process_button__8:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 8);
    __asm__ __volatile__("keyboard__port_a__process_button__7:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 7);
    __asm__ __volatile__("keyboard__port_a__process_button__6:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 6);
    __asm__ __volatile__("keyboard__port_a__process_button__5:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 5);
    __asm__ __volatile__("keyboard__port_a__process_button__4:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 4);
    __asm__ __volatile__("keyboard__port_a__process_button__3:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 3);
    __asm__ __volatile__("keyboard__port_a__process_button__2:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 2);
    __asm__ __volatile__("keyboard__port_a__process_button__1:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 1);
    __asm__ __volatile__("keyboard__port_a__process_button__0:");
    keyboard__port_a__process_button(keyboard__port_a__state, changes, 0);
}

void keyboard__port_a__check_for_changes_and_process(void) {
    __asm__ __volatile__("keyboard__port_a__process:");
    uint8_t keyboard__port_a__state = PINA;
    uint8_t changes = keyboard__port_a__mask & ((uint8_t) (keyboard__port_a__previous_state ^ keyboard__port_a__state));
    if (changes) {
        keyboard__port_a__process_events(keyboard__port_a__state, changes);
        keyboard__debounce_timer__start();
    }
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

inline void keyboard__port_b__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_b__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        keyboard__port_b__mask &= (uint8_t) ~((uint8_t) (1U << pin));
        COPY_BIT(state, pin, keyboard__port_b__previous_state, pin);
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_b__process_events(uint8_t keyboard__port_b__state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_b__process_button__15:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 15);
    __asm__ __volatile__("keyboard__port_b__process_button__14:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 14);
    __asm__ __volatile__("keyboard__port_b__process_button__13:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 13);
    __asm__ __volatile__("keyboard__port_b__process_button__12:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 12);
    __asm__ __volatile__("keyboard__port_b__process_button__11:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 11);
    __asm__ __volatile__("keyboard__port_b__process_button__10:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 10);
    __asm__ __volatile__("keyboard__port_b__process_button__9:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 9);
    __asm__ __volatile__("keyboard__port_b__process_button__8:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 8);
    __asm__ __volatile__("keyboard__port_b__process_button__7:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 7);
    __asm__ __volatile__("keyboard__port_b__process_button__6:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 6);
    __asm__ __volatile__("keyboard__port_b__process_button__5:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 5);
    __asm__ __volatile__("keyboard__port_b__process_button__4:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 4);
    __asm__ __volatile__("keyboard__port_b__process_button__3:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 3);
    __asm__ __volatile__("keyboard__port_b__process_button__2:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 2);
    __asm__ __volatile__("keyboard__port_b__process_button__1:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 1);
    __asm__ __volatile__("keyboard__port_b__process_button__0:");
    keyboard__port_b__process_button(keyboard__port_b__state, changes, 0);
}

void keyboard__port_b__check_for_changes_and_process(void) {
    __asm__ __volatile__("keyboard__port_b__process:");
    uint8_t keyboard__port_b__state = PINB;
    uint8_t changes = keyboard__port_b__mask & ((uint8_t) (keyboard__port_b__previous_state ^ keyboard__port_b__state));
    if (changes) {
        keyboard__port_b__process_events(keyboard__port_b__state, changes);
        keyboard__debounce_timer__start();
    }
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

inline void keyboard__port_c__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_c__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        keyboard__port_c__mask &= (uint8_t) ~((uint8_t) (1U << pin));
        COPY_BIT(state, pin, keyboard__port_c__previous_state, pin);
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_c__process_events(uint8_t keyboard__port_c__state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_c__process_button__15:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 15);
    __asm__ __volatile__("keyboard__port_c__process_button__14:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 14);
    __asm__ __volatile__("keyboard__port_c__process_button__13:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 13);
    __asm__ __volatile__("keyboard__port_c__process_button__12:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 12);
    __asm__ __volatile__("keyboard__port_c__process_button__11:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 11);
    __asm__ __volatile__("keyboard__port_c__process_button__10:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 10);
    __asm__ __volatile__("keyboard__port_c__process_button__9:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 9);
    __asm__ __volatile__("keyboard__port_c__process_button__8:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 8);
    __asm__ __volatile__("keyboard__port_c__process_button__7:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 7);
    __asm__ __volatile__("keyboard__port_c__process_button__6:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 6);
    __asm__ __volatile__("keyboard__port_c__process_button__5:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 5);
    __asm__ __volatile__("keyboard__port_c__process_button__4:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 4);
    __asm__ __volatile__("keyboard__port_c__process_button__3:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 3);
    __asm__ __volatile__("keyboard__port_c__process_button__2:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 2);
    __asm__ __volatile__("keyboard__port_c__process_button__1:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 1);
    __asm__ __volatile__("keyboard__port_c__process_button__0:");
    keyboard__port_c__process_button(keyboard__port_c__state, changes, 0);
}


void keyboard__port_c__check_for_changes_and_process(void) {
    __asm__ __volatile__("keyboard__port_c__process:");
    uint8_t keyboard__port_c__state = PINC;
    uint8_t changes = keyboard__port_c__mask & ((uint8_t) (keyboard__port_c__state ^ keyboard__port_c__previous_state));
    if (changes) {
        keyboard__debounce_timer__start();
        keyboard__port_c__process_events(keyboard__port_c__state, changes);
    }
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

inline void keyboard__port_d__process_button(uint8_t state, uint8_t changes, uint8_t button) {
    uint8_t pin = keyboard__pins__port_d__pin_for_button(button);
    if (changes & ((uint8_t) (1U << pin))) {
        keyboard__port_d__mask &= (uint8_t) ~((uint8_t) (1U << pin));
        COPY_BIT(state, pin, keyboard__port_d__previous_state, pin);
        keyboard__handle_button_event(button, state, pin);
    }
}


void keyboard__port_d__process_events(uint8_t keyboard__port_d__state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_d__process_button__15:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 15);
    __asm__ __volatile__("keyboard__port_d__process_button__14:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 14);
    __asm__ __volatile__("keyboard__port_d__process_button__13:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 13);
    __asm__ __volatile__("keyboard__port_d__process_button__12:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 12);
    __asm__ __volatile__("keyboard__port_d__process_button__11:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 11);
    __asm__ __volatile__("keyboard__port_d__process_button__10:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 10);
    __asm__ __volatile__("keyboard__port_d__process_button__9:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 9);
    __asm__ __volatile__("keyboard__port_d__process_button__8:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 8);
    __asm__ __volatile__("keyboard__port_d__process_button__7:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 7);
    __asm__ __volatile__("keyboard__port_d__process_button__6:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 6);
    __asm__ __volatile__("keyboard__port_d__process_button__5:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 5);
    __asm__ __volatile__("keyboard__port_d__process_button__4:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 4);
    __asm__ __volatile__("keyboard__port_d__process_button__3:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 3);
    __asm__ __volatile__("keyboard__port_d__process_button__2:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 2);
    __asm__ __volatile__("keyboard__port_d__process_button__1:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 1);
    __asm__ __volatile__("keyboard__port_d__process_button__0:");
    keyboard__port_d__process_button(keyboard__port_d__state, changes, 0);
}


void keyboard__port_d__check_for_changes_and_process(void) {
    __asm__ __volatile__("keyboard__port_d__process:");
    uint8_t keyboard__port_d__state = PIND;
    uint8_t changes = keyboard__port_d__mask & ((uint8_t) (keyboard__port_d__state ^ keyboard__port_d__previous_state));
    if (changes) {
        keyboard__debounce_timer__start();
        keyboard__port_d__process_events(keyboard__port_d__state, changes);
    }
}
#endif


void keyboard__run(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__check_for_changes_and_process();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__check_for_changes_and_process();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__check_for_changes_and_process();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__check_for_changes_and_process();
#endif
}
