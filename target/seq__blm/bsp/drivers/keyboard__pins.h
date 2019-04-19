#ifndef KEYBOARD__PINS_H
#define KEYBOARD__PINS_H

#include "cpu/avr/gpio.h" //CONCAT


void keyboard__pins__init(void);

/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_b__pin_for_button(const uint8_t button);

/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_c__pin_for_button(const uint8_t button);

/**
 * Provides pin number for the given button (if it pertains to port D)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_d__pin_for_button(const uint8_t button);


#endif
