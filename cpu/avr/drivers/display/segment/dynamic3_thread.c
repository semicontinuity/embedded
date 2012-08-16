// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Implements dynamic lighting.
//
// Usage:
//
// To initialize, call display_thread__init().
// Then, call display_thread__run() periodically, e.g. 250 times per second.
//
// Put the data to be displayed into display_thread__segments.
//
// Blinking support:
//
// To turn on blinking, call display_thread__blink__on().
// To turn off blinking, call display_thread__blink__off().
// Call display_thread__phase_on() and display_thread__phase_off() periodically.
// =============================================================================
#include <stdint.h>
#include "cpu/avr/drivers/display/segment/dynamic3_thread.h"
#include "cpu/avr/drivers/display/segment/dynamic3.h"
#include "cpu/avr/drivers/display/segment/values.h"

/**
 * The data to be displayed.
 * These are the raw segment data to be writen to the segments port.
 */
volatile uint8_t display_thread__segments[3] = {
    DISPLAY_SEGMENT_VALUE_EMPTY,
    DISPLAY_SEGMENT_VALUE_EMPTY,
    DISPLAY_SEGMENT_VALUE_EMPTY
};

/**
 * Blink flag.
 * 0: The display is not blinking.
 * 1: The display is blinking.
 */
volatile uint8_t display_thread__blink;


/**
 * Display thread constructor.
 */
INLINE void display_thread__init(void) {
    display__init();
    display__on();
}


/**
 * Display thread state.
 * 0: Digit 1 displayed
 * 1: Digit 2 displayed
 * 2: Digit 3 displayed
 */
int8_t display_thread__state;


/**
 * Invoked periodically (every system tick) to implement dynamic display.
 */
INLINE void display_thread__run(void) {
    --display_thread__state;
    if (display_thread__state < 0) {
        display_thread__state = 2; // roll over

        display__digit_1__deselect();
        display__segments__set(display_thread__segments[2]);
        display__digit_3__select();
    }
    else if (display_thread__state == 0) {
        display__digit_2__deselect();
        display__segments__set(display_thread__segments[0]);
        display__digit_1__select();
    }
    else /* new state is 1 */ {
        display__digit_3__deselect();
        display__segments__set(display_thread__segments[1]);
        display__digit_2__select();
    }
}


INLINE void display_thread__blink__on(void) {
    display_thread__blink = 1;
}


INLINE void display_thread__blink__off(void) {
    display_thread__blink = 0;
    display__on();
}


INLINE void display_thread__phase_on(void) {
    if (display_thread__blink) {
        display__on();
    }
}


INLINE void display_thread__phase_off(void) {
    if (display_thread__blink) {
        display__off();
    }
}
