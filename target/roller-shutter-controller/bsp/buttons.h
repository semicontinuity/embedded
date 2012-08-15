#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize the button pins
 */
INLINE void buttons__init(void);

/**
 * Called periodically to scan buttons
 */
INLINE void buttons__run(void);



#define button1__is_pressed()   (IS_0(BUTTON1))
#define button1__was_pressed()  (~buttons__state & _BV(BUTTON1__PIN))
#define button1__was_released() (buttons__state & _BV(BUTTON1__PIN))

/**
 * Callback function, that must be implemented by the user.
 * Called when BUTTON1 has been just pressed or released.
 */
INLINE void buttons__on_button1_changed(void);



#define button2__is_pressed()   (IS_0(BUTTON2))
#define button2__was_pressed()  (~buttons__state & _BV(BUTTON2__PIN))
#define button2__was_released() (buttons__state & _BV(BUTTON2__PIN))

/**
 * Callback function, that must be implemented by the user.
 * Called when BUTTON2 has been just pressed or released.
 */
INLINE void buttons__on_button2_changed(void);



#endif