// =============================================================================
// The thread (service) that renders patterns on red+green LED.
// =============================================================================

#include <stdint.h>
#include "led.h"
#include "led_thread.h"


volatile led_thread__mode_t led_thread__mode;


INLINE void led_thread__init(void) {
    led_green__init();
    led_red__init();
}

/**
 * Set the LED color to black.
 * The change is effective immediately.
 */
INLINE void led_thread__set_black() {
    led_green__off();
    led_red__off();
    led_thread__mode = LED_THREAD__MODE__BLACK;
}

/**
 * Set the LED color to green.
 * The change is effective immediately.
 */
INLINE void led_thread__set_green() {
    led_green__on();
    led_red__off();
    led_thread__mode = LED_THREAD__MODE__GREEN;
}

/**
 * Set the LED color to green.
 * The change is effective immediately.
 */
INLINE void led_thread__set_red() {
    led_green__off();
    led_red__on();
    led_thread__mode = LED_THREAD__MODE__RED;
}

/**
 * Set the LED mode.
 * Should be used mainly for modes when LED is blinking.
 * The change is effective at the start of the next phase.
 */
INLINE void led_thread__mode__set(const led_thread__mode_t mode) {
    led_thread__mode = mode;
}


inline void led_thread__render(const uint8_t flags) {
    // Red has priority over green (for spurious state changes - display red)
    if (flags & LED_THREAD__RED) led_red__on(); else led_red__off();
    if (flags & LED_THREAD__GREEN) led_green__on(); else led_green__off();
}


INLINE void led_thread__phase_on(void) {
    led_thread__render(led_thread__mode);
}


INLINE void led_thread__phase_off(void) {
    led_thread__render(led_thread__mode >> 4);
}
