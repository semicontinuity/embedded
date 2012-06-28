#ifndef __LED_THREAD_H
#define __LED_THREAD_H

#include <stdint.h>
#include "led.h"

#define LED_THREAD__BLACK       (0)
#define LED_THREAD__GREEN       (1)
#define LED_THREAD__RED         (2)

// Modes for blinking

#define LED_THREAD__MODE__BLACK         (LED_THREAD__BLACK        | LED_THREAD__BLACK<<4)
#define LED_THREAD__MODE__BLACK_GREEN   (LED_THREAD__BLACK        | LED_THREAD__GREEN<<4)
#define LED_THREAD__MODE__BLACK_RED     (LED_THREAD__BLACK        | LED_THREAD__RED<<4  )

#define LED_THREAD__MODE__GREEN_BLACK   (LED_THREAD__GREEN        | LED_THREAD__BLACK<<4)
#define LED_THREAD__MODE__GREEN         (LED_THREAD__GREEN        | LED_THREAD__GREEN<<4)
#define LED_THREAD__MODE__GREEN_RED     (LED_THREAD__GREEN        | LED_THREAD__RED<<4  )

#define LED_THREAD__MODE__RED_BLACK     (LED_THREAD__RED          | LED_THREAD__BLACK<<4)
#define LED_THREAD__MODE__RED_GREEN     (LED_THREAD__RED          | LED_THREAD__GREEN<<4)
#define LED_THREAD__MODE__RED           (LED_THREAD__RED          | LED_THREAD__RED<<4  )

INLINE void led_thread__init(void) {
    led_green__init();
    led_red__init();
}

/**
 * Set the LED color to black.
 * The change is effective immediately.
 */
INLINE void led_thread__set_black(void);

/**
 * Set the LED color to green.
 * The change is effective immediately.
 */
INLINE void led_thread__set_green(void);

/**
 * Set the LED color to green.
 * The change is effective immediately.
 */
INLINE void led_thread__set_red(void);

/**
 * Set the LED mode.
 * Should be used mainly for modes when LED is blinking.
 * The change is effective at the start of the next phase.
 */
INLINE void led_thread__mode__set(uint8_t mode);

INLINE void led_thread__phase_on(void);
INLINE void led_thread__phase_off(void);


#endif