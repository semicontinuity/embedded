// =============================================================================
// The driver for 3 buttons at pins BUTTON1, BUTTON2 and BUTTON3,
// all on the same BUTTONS__PORT.
// Does not support concurrent button presses.
// =============================================================================
#include "device.h"

#include "buttons.h"
#include <stdint.h>
#include <avr/io.h>
#include "cpu/avr/gpio.h"


// Support for repeated key events.
// REPEAT_DELAY and REPEAT_PERIOD must be different, greater than 0 and less than 256

// The initial delay of repeat events is 250 system ticks (1 second)
#define BUTTONS__REPEAT_DELAY (250)
// The initial delay of repeat events is 25 system ticks (0.1 seconds)
#define BUTTONS__REPEAT_PERIOD (25)

#define BUTTONS_MASK (_BV(BUTTON1__PIN) | _BV(BUTTON2__PIN) | _BV(BUTTON3__PIN))

uint8_t buttons__state = BUTTONS_MASK;
uint8_t buttons__changed;
uint8_t buttons__time;
uint8_t buttons__repeat_phase;


inline void button1__init(void) {
    USE_AS_INPUT(BUTTON1);
    ENABLE_PULLUP(BUTTON1);
}

inline void button2__init(void) {
    USE_AS_INPUT(BUTTON2);
    ENABLE_PULLUP(BUTTON2);
}

inline void button3__init(void) {
    USE_AS_INPUT(BUTTON3);
    ENABLE_PULLUP(BUTTON3);
}

INLINE void buttons__init(void) {
    button1__init();
    button2__init();
    button3__init();
}


INLINE uint8_t buttons__delay_elapsed(void)                     { return buttons__time == 0 && buttons__repeat_phase == 0; }

INLINE uint8_t button1__was_changed(void)                       { return buttons__changed & _BV(BUTTON1__PIN); }
INLINE uint8_t button2__was_changed(void)                       { return buttons__changed & _BV(BUTTON2__PIN); }
INLINE uint8_t button3__was_changed(void)                       { return buttons__changed & _BV(BUTTON3__PIN); }


INLINE uint8_t button1__was_pressed(void)                       { return ~buttons__state & _BV(BUTTON1__PIN); }
INLINE uint8_t button2__was_pressed(void)                       { return ~buttons__state & _BV(BUTTON2__PIN); }
INLINE uint8_t button3__was_pressed(void)                       { return ~buttons__state & _BV(BUTTON3__PIN); }

INLINE uint8_t button1__was_released(void)                      { return buttons__state & _BV(BUTTON1__PIN); }
INLINE uint8_t button2__was_released(void)                      { return buttons__state & _BV(BUTTON2__PIN); }
INLINE uint8_t button3__was_released(void)                      { return buttons__state & _BV(BUTTON3__PIN); }


INLINE uint8_t button1__was_just_pressed(void)                  { return button1__was_changed() & ~buttons__state;}
INLINE uint8_t button2__was_just_pressed(void)                  { return button2__was_changed() & ~buttons__state;}
INLINE uint8_t button3__was_just_pressed(void)                  { return button3__was_changed() & ~buttons__state;}

INLINE uint8_t button1__was_just_released(void)                 { return button1__was_changed() & buttons__state;}
INLINE uint8_t button2__was_just_released(void)                 { return button2__was_changed() & buttons__state;}
INLINE uint8_t button3__was_just_released(void)                 { return button3__was_changed() & buttons__state;}

INLINE uint8_t button1__was_just_pressed_or_repeated(void)      { return button1__was_pressed() && (button1__was_changed() || buttons__time == 0);}
INLINE uint8_t button2__was_just_pressed_or_repeated(void)      { return button2__was_pressed() && (button2__was_changed() || buttons__time == 0);}
INLINE uint8_t button3__was_just_pressed_or_repeated(void)      { return button3__was_pressed() && (button3__was_changed() || buttons__time == 0);}


/**
 * Called periodically to scan buttons
 */
INLINE void buttons__run(void) {
    uint8_t current_state = PORT_VALUE(BUTTONS) & BUTTONS_MASK;
    if ((buttons__changed = buttons__state ^ current_state)) {
        buttons__time = BUTTONS__REPEAT_DELAY;
        buttons__state = current_state;
        buttons__repeat_phase = 0;
    }
    else {
        if (buttons__time > 0) {
            --buttons__time;
        }
        else {
            buttons__time = BUTTONS__REPEAT_PERIOD;
            buttons__repeat_phase = 1;
        }
    }
}
