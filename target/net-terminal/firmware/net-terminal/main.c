#include "drivers/out/lcd_backlight.h"
#include "flags/password__changed.h"

#include "kernel.h"

#include "alarm_client__auth.h"
#include "alarm_client__ui.h"
#include "services/lcd_backlight_fader.h"
#include "services/lcd_backlight_service.h"
#include "keypad.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "system_timer.h"
//#include "console_service.h"

//#include <avr/pgmspace.h>
#include <avr/interrupt.h>
//#include <util/delay.h>


// =============================================================================
// Services binding
// =============================================================================

/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    keypad__run();
    lcd_backlight_fader__run();
    lcd_backlight_service__run();
}

INLINE void keypad__on_event(const uint8_t keyevent) {
    lcd_backlight_service__signal();
    alarm_client__ui__on_key_event(keyevent);
}

// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Outputs
    lcd_backlight__init();

    // Flags
    password__changed__init();

    // Drivers
    system_timer__init();

    // Services
    keypad__init();
    terminal_init();
    alarm_client__auth__init();
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
//    console_service__init();

        kernel__init();
        kernel__start();

        application__init();
        application__start();

    sei();
    for(;;);
//    console_service__run();

    return 0;
}
