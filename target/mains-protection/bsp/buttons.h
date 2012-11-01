// =============================================================================
// The driver for 3 buttons at pins BUTTON1, BUTTON2 and BUTTON3,
// all on the same BUTTONS__PORT.
// Does not support concurrent button presses.
// =============================================================================

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


#define button1__is_pressed() (IS_0(BUTTON1))
#define button2__is_pressed() (IS_0(BUTTON2))
#define button3__is_pressed() (IS_0(BUTTON3))

INLINE uint8_t buttons__delay_elapsed(void);

INLINE uint8_t button1__was_changed(void);
INLINE uint8_t button2__was_changed(void);
INLINE uint8_t button3__was_changed(void);

INLINE uint8_t button1__was_pressed(void);
INLINE uint8_t button2__was_pressed(void);
INLINE uint8_t button3__was_pressed(void);

INLINE uint8_t button1__was_released(void);
INLINE uint8_t button2__was_released(void);
INLINE uint8_t button3__was_released(void);

INLINE uint8_t button1__was_just_pressed(void);
INLINE uint8_t button2__was_just_pressed(void);
INLINE uint8_t button3__was_just_pressed(void);

INLINE uint8_t button1__was_just_released(void);
INLINE uint8_t button2__was_just_released(void);
INLINE uint8_t button3__was_just_released(void);

INLINE uint8_t button1__was_just_pressed_or_repeated(void);
INLINE uint8_t button2__was_just_pressed_or_repeated(void);
INLINE uint8_t button3__was_just_pressed_or_repeated(void);


/**
 * Initialize the button pins
 */
INLINE void buttons__init(void);

/**
 * Called periodically to scan buttons
 */
INLINE void buttons__run(void);


#endif