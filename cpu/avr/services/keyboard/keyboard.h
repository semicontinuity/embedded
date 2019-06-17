#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
void keyboard__port_a__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_a__mask__clear_bit(uint8_t bit);
#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
void keyboard__port_b__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_b__mask__clear_bit(uint8_t bit);
#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
void keyboard__port_c__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_c__mask__clear_bit(uint8_t bit);
#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
void keyboard__port_d__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_d__mask__clear_bit(uint8_t bit);
#endif


void keyboard__init(void);

void keyboard__run(void);

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit);

#endif
