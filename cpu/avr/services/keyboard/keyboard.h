#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
void keyboard__port_a__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_a__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_a__mask__clear_bit(uint8_t bit);
void keyboard__port_a__mask__and_with(uint8_t mask);
#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
void keyboard__port_b__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_b__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_b__mask__clear_bit(uint8_t bit);
void keyboard__port_b__mask__and_with(uint8_t mask);
#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
void keyboard__port_c__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_c__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_c__mask__clear_bit(uint8_t bit);
void keyboard__port_c__mask__and_with(uint8_t mask);
#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
void keyboard__port_d__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_d__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_d__mask__clear_bit(uint8_t bit);
void keyboard__port_d__mask__and_with(uint8_t mask);
#endif


void keyboard__init(void);

void keyboard__run(void);

void keyboard__reset_masks(void);

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-31)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit);


/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then increment encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then decrement encoder's value;
 * @param encoder index of encoder (0-3)
 */
void keyboard__encoders__increment_if_bit_set(uint8_t encoder, uint8_t state, uint8_t bit);

/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then decrement encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then increment encoder's value;
 * @param encoder index of encoder (0-3)
 */
void keyboard__encoders__decrement_if_bit_set(uint8_t encoder, uint8_t state, uint8_t bit);


#endif
