#ifndef KEYBOARD__PINS__MAPPING_H
#define KEYBOARD__PINS__MAPPING_H

#include <stdint.h>

// =============================================================================

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#include "cpu/avr/drivers/keyboard/keyboard__port_a__pins__mapping.h"

/**
 * Provides pin number for the given button (if it pertains to port A)
 * @param button 0-31 for BUTTON0..BUTTON31
*/
uint8_t keyboard__pins__port_a__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_a__button_pins_mask(void);

/**
 * Provides pin number for the given encoder A pin (if it pertains to port A)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_a__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port A)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_a__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_a__encoders_pins_mask(void);

#endif

// =============================================================================

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#include "cpu/avr/drivers/keyboard/keyboard__port_b__pins__mapping.h"

/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-31 for BUTTON0..BUTTON31
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
uint8_t keyboard__pins__port_b__pin_a_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_b__encoders_pins_mask(void);

#endif

// =============================================================================

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#include "cpu/avr/drivers/keyboard/keyboard__port_c__pins__mapping.h"

/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-31 for BUTTON0..BUTTON31
*/
uint8_t keyboard__pins__port_c__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_c__button_pins_mask(void);

/**
 * Provides pin number for the given encoder A pin (if it pertains to port C)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_c__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port C)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_c__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_c__encoders_pins_mask(void);

#endif

// =============================================================================

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#include "cpu/avr/drivers/keyboard/keyboard__port_d__pins__mapping.h"

/**
 * Provides pin number for the given button (if it pertains to port D)
 * @param button 0-31 for BUTTON0..BUTTON31
*/
uint8_t keyboard__pins__port_d__pin_for_button(const uint8_t button);

uint8_t keyboard__pins__port_d__button_pins_mask(void);

/**
 * Provides pin number for the given encoder D pin (if it pertains to port D)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_d__pin_a_for_encoder(const uint8_t encoder);

/**
 * Provides pin number for the given encoder B pin (if it pertains to port D)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_d__pin_b_for_encoder(const uint8_t encoder);

uint8_t keyboard__pins__port_d__encoders_pins_mask(void);

#endif


#endif
