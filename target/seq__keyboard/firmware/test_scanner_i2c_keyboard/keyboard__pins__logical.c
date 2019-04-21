#include "drivers/keyboard__pins.h"
#include "keyboard__pins__logical.h"


void keyboard__pins__init(void) {
}


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__STATE__REG
register volatile uint8_t keyboard__port_a__state asm(QUOTE(KEYBOARD__PORT_A__STATE__REG));
#else
volatile uint8_t keyboard__port_a__state;
#endif

void keyboard__pins__port_a__state__set(const uint8_t state) {
    keyboard__port_a__state = state;
}

uint8_t keyboard__pins__port_a__read(void) {
    return keyboard__port_a__state;
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#ifdef KEYBOARD__PORT_B__STATE__REG
register volatile uint8_t keyboard__port_b__state asm(QUOTE(KEYBOARD__PORT_B__STATE__REG));
#else
volatile uint8_t keyboard__port_b__state;
#endif

void keyboard__pins__port_b__state__set(const uint8_t state) {
    keyboard__port_b__state = state;
}

uint8_t keyboard__pins__port_b__read(void) {
    return keyboard__port_b__state;
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#ifdef KEYBOARD__PORT_C__STATE__REG
register volatile uint8_t keyboard__port_c__state asm(QUOTE(KEYBOARD__PORT_C__STATE__REG));
#else
volatile uint8_t keyboard__port_c__state;
#endif

void keyboard__pins__port_c__state__set(const uint8_t state) {
    keyboard__port_c__state = state;
}

uint8_t keyboard__pins__port_c__read(void) {
    return keyboard__port_c__state;
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#ifdef KEYBOARD__PORT_D__STATE__REG
register volatile uint8_t keyboard__port_d__state asm(QUOTE(KEYBOARD__PORT_D__STATE__REG));
#else
volatile uint8_t keyboard__port_d__state;
#endif

void keyboard__pins__port_d__state__set(const uint8_t state) {
    keyboard__port_d__state = state;
}

uint8_t keyboard__pins__port_d__read(void) {
    return keyboard__port_d__state;
}

#endif


/**
 * Provides pin number for the given button (if it pertains to port A)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_a__pin_for_button(const uint8_t button) {
    return 0U;
}

/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_b__pin_for_button(const uint8_t button) {
    return 0U;
}

/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_c__pin_for_button(const uint8_t button) {
    return 0U;
}

/**
 * Provides pin number for the given button (if it pertains to port D)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_d__pin_for_button(const uint8_t button) {
    return 0U;
}


uint8_t keyboard__pins__port_a__button_pins_mask(void) {
    return 0U;
}

uint8_t keyboard__pins__port_b__button_pins_mask(void) {
    return 0U;
}

uint8_t keyboard__pins__port_c__button_pins_mask(void) {
    return 0U;
}

uint8_t keyboard__pins__port_d__button_pins_mask(void) {
    return 0U;
}

