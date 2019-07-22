#ifndef KEYBOARD__PORT_B__PINS__MAPPING_H
#define KEYBOARD__PORT_B__PINS__MAPPING_H

#include <stdint.h>


/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_b__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_b__button_pins_mask(void);


/**
 * Provides pin number for the given encoder A pin (if it pertains to port B)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_b__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port B)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_b__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_b__encoders_pins_mask(void);


uint8_t keyboard__pins__port_b__pins_mask(void);


#endif
