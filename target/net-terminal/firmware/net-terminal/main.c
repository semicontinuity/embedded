#include "out/amplifier_relay.h"
#include "out/siren1.h"
#include "out/siren2.h"
#include "out/water_valve.h"

#include "kernel.h"

#include "alarm_client__auth.h"
#include "lcd_backlight_service.h"
#include "keypad.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "system_timer.h"
//#include "console_service.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    keypad__run();
}

INLINE void keypad__on_event(const uint8_t keyevent) {
    terminal_displayChar(0x40 + keyevent);
}

// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {
    out__amplifier_relay__init();
    out__siren1__init();
    out__siren2__init();
    out__water_valve__init();

    keypad__init();
    terminal_init();
    alarm_client__auth__init();
    system_timer__init();
}

inline static void application__start(void) {
    system_timer__start();
}

inline static void application__stop(void) {
    system_timer__stop();
}



int main(void) {
//    console_service__init();
    lcd_backlight_service__init();

        kernel__init();
        kernel__start();

        application__init();
        application__start();

    sei();
    for(;;);
//    console_service__run();

    return 0;
}
