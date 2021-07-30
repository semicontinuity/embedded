#ifndef KEYBOARD__PORT_F__PINS__MAPPING_H
#define KEYBOARD__PORT_F__PINS__MAPPING_H

#include <stdint.h>


/**
 * Provides pin number for the given button (if it pertains to port F)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_f__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_f__button_pins_mask(void);


/**
 * Provides pin number for the given encoder A pin (if it pertains to port F)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_f__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port F)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_f__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_f__encoders_pins_mask(void);


uint8_t keyboard__pins__port_f__pins_mask(void);


#endif
