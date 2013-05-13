#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "drivers/keypad.h"
#include "drivers/system_timer.h"
#include <avr/interrupt.h>


// =============================================================================
// Services binding
// =============================================================================

/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    keypad__run();
}

void keypad__on_event(const uint8_t keyevent) {
    terminal_displayChar(keyevent);
}

// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Drivers
    terminal_init();
    keypad__init();
    system_timer__init();
}


inline static void application__start(void) {
    system_timer__start();
}

inline static void application__stop(void) {
    system_timer__stop();
}


// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    application__init();
    application__start();

    sei();
    for(;;);
    return 0;
}
