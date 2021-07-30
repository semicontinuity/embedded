#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <cpu/avr/macros.h>


#ifdef KEYBOARD__COMMON_MASK__REG
register volatile uint8_t keyboard__common_mask asm(QUOTE(KEYBOARD__COMMON_MASK__REG));
#endif


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer.h>
void keyboard__port_a__init_previous_state(void);
void keyboard__port_a__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_a__mask__clear_bit(uint8_t bit);
void keyboard__port_a__mask__and_with(uint8_t mask);
void keyboard__port_a__mask__reset(void);
void keyboard__port_a__run(void);
#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h>
void keyboard__port_b__init_previous_state(void);
void keyboard__port_b__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_b__mask__clear_bit(uint8_t bit);
void keyboard__port_b__mask__and_with(uint8_t mask);
void keyboard__port_b__mask__reset(void);
void keyboard__port_b__run(void);
#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h>
void keyboard__port_c__init_previous_state(void);
void keyboard__port_c__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_c__mask__clear_bit(uint8_t bit);
void keyboard__port_c__mask__and_with(uint8_t mask);
void keyboard__port_c__mask__reset(void);
void keyboard__port_c__run(void);
#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h>
void keyboard__port_d__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_d__init_previous_state(void);
void keyboard__port_d__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_d__mask__clear_bit(uint8_t bit);
void keyboard__port_d__mask__and_with(uint8_t mask);
void keyboard__port_d__mask__reset(void);
void keyboard__port_d__run(void);
#endif


#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_e__debounce_timer.h>
void keyboard__port_e__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_e__init_previous_state(void);
void keyboard__port_e__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_e__mask__clear_bit(uint8_t bit);
void keyboard__port_e__mask__and_with(uint8_t mask);
void keyboard__port_e__mask__reset(void);
void keyboard__port_e__run(void);
#endif


#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_f__debounce_timer.h>
void keyboard__port_f__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_f__init_previous_state(void);
void keyboard__port_f__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_f__mask__clear_bit(uint8_t bit);
void keyboard__port_f__mask__and_with(uint8_t mask);
void keyboard__port_f__mask__reset(void);
void keyboard__port_f__run(void);
#endif


#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_g__debounce_timer.h>
void keyboard__port_g__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_g__init_previous_state(void);
void keyboard__port_g__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_g__mask__clear_bit(uint8_t bit);
void keyboard__port_g__mask__and_with(uint8_t mask);
void keyboard__port_g__mask__reset(void);
void keyboard__port_g__run(void);
#endif


#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
#include <cpu/avr/drivers/keyboard/keyboard__port_h__debounce_timer.h>
void keyboard__port_h__debounce_timer__start(void) __attribute__((weak));
void keyboard__port_h__init_previous_state(void);
void keyboard__port_h__previous_state__copy_bit(uint8_t state, uint8_t bit);
void keyboard__port_h__mask__clear_bit(uint8_t bit);
void keyboard__port_h__mask__and_with(uint8_t mask);
void keyboard__port_h__mask__reset(void);
void keyboard__port_h__run(void);
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
