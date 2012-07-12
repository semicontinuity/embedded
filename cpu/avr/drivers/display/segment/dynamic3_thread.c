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
#include "device.h"

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


INLINE void display_thread__init(void) {
    display_init();
    display_on();

    // TODO: try to remove
    display__segments__set(DISPLAY_SEGMENT_VALUE_EMPTY);
    display_select_digit_1();
}


/**
 * Display thread state.
 * 0: Digit 1 displayed
 * 1: Digit 2 displayed
 * 2: Digit 3 displayed
 */
int8_t display_thread__state;


INLINE void display_thread__run(void) {

    --display_thread__state;
    if (display_thread__state < 0) {
        display_thread__state = 2;
        display_deselect_digit_1();
        display__segments__set(display_thread__segments[2]);
        display_select_digit_3();
    }
    else if (display_thread__state == 0) {
        display_deselect_digit_2();
        display__segments__set(display_thread__segments[0]);
        display_select_digit_1();
    }
    else /* new state is 1 */ {
        display_deselect_digit_3();
        display__segments__set(display_thread__segments[1]);
        display_select_digit_2();
    }
}


INLINE void display_thread__blink__on(void) {
    display_thread__blink = 1;
}


INLINE void display_thread__blink__off(void) {
    display_thread__blink = 0;
    display_on();
}


INLINE void display_thread__phase_on(void) {
    if (display_thread__blink) {
        display_on();
    }
}


INLINE void display_thread__phase_off(void) {
    if (display_thread__blink) {
        display_off();
    }
}
