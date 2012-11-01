// =============================================================================
// The thread (service) that renders patterns on red+green LED.
// See the list of LED_THREAD__MODE constants for patterns that can be rendered.
// =============================================================================

#ifndef __LED_THREAD_H
#define __LED_THREAD_H

#include <stdint.h>
#include "led.h"

#define LED_THREAD__BLACK       (0)
#define LED_THREAD__GREEN       (1)
#define LED_THREAD__RED         (2)


typedef enum {
    LED_THREAD__MODE__BLACK         = (LED_THREAD__BLACK        | LED_THREAD__BLACK<<4),
    LED_THREAD__MODE__BLACK_GREEN   = (LED_THREAD__BLACK        | LED_THREAD__GREEN<<4),
    LED_THREAD__MODE__BLACK_RED     = (LED_THREAD__BLACK        | LED_THREAD__RED<<4  ),

    LED_THREAD__MODE__GREEN_BLACK   = (LED_THREAD__GREEN        | LED_THREAD__BLACK<<4),
    LED_THREAD__MODE__GREEN         = (LED_THREAD__GREEN        | LED_THREAD__GREEN<<4),
    LED_THREAD__MODE__GREEN_RED     = (LED_THREAD__GREEN        | LED_THREAD__RED<<4  ),

    LED_THREAD__MODE__RED_BLACK     = (LED_THREAD__RED          | LED_THREAD__BLACK<<4),
    LED_THREAD__MODE__RED_GREEN     = (LED_THREAD__RED          | LED_THREAD__GREEN<<4),
    LED_THREAD__MODE__RED           = (LED_THREAD__RED          | LED_THREAD__RED<<4  )
} led_thread__mode_t;


/**
 * Initialize the LED thread.
 */
INLINE void led_thread__init(void);

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
INLINE void led_thread__mode__set(led_thread__mode_t mode);

INLINE void led_thread__phase_on(void);
INLINE void led_thread__phase_off(void);


#endif