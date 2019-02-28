#ifndef KEYBOARD__INTERRUPTS_H
#define KEYBOARD__INTERRUPTS_H

#include <stdint.h>

void keyboard__interrupts__init(void);

void keyboard__interrupts__start(void);

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline void keyboard__interrupts__handle_button_event(uint8_t button, uint8_t state, uint8_t bit);

#endif
