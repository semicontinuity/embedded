#ifndef KEYBOARD__PORT_E__PINS__MAPPING_H
#define KEYBOARD__PORT_E__PINS__MAPPING_H

#include <stdint.h>


/**
 * Provides pin number for the given button (if it pertains to port E)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_e__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_e__button_pins_mask(void);


/**
 * Provides pin number for the given encoder A pin (if it pertains to port E)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_e__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port E)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_e__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_e__encoders_pins_mask(void);


uint8_t keyboard__pins__port_e__pins_mask(void);


#endif
