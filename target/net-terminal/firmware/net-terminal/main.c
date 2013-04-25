#include "drivers/in/sensors.h"
#include "drivers/out/lcd_backlight.h"

#include "drivers/system_timer.h"
#include "drivers/keypad.h"

#include "flags/password__changed.h"

#include "kernel.h"

#include "alarm_client__auth.h"
#include "alarm_client__state.h"
#include "alarm_client__ui.h"

#include "comm_service__endpoint__alarm_client__state.h"
#include "comm_service__endpoint__sensors.h"

#include "services/lcd_backlight_fader.h"
#include "services/lcd_backlight_service.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"

//#include "console_service.h"

//#include <avr/pgmspace.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

const char CONNECTING[] PROGMEM = "Соединение с сервером\n";


// =============================================================================
// Services binding
// =============================================================================

/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    keypad__run();
    lcd_backlight_service__run();
    lcd_backlight_fader__run();
    sensors__run();
}


INLINE void keypad__on_event(const uint8_t keyevent) {
    lcd_backlight_service__signal();
    alarm_client__ui__on_key_event(keyevent);
}


INLINE void alarm_client__state__on_changed(void) {
    alarm_client__ui__on_state_changed();
}


INLINE void alarm_client__new_state__on_changed(void) {
    comm_service__endpoint__alarm_client__state__send();
}


void sensors__status__on_change(void) {
    comm_service__endpoint__sensors__send();
}


// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Outputs
    lcd_backlight__init();

    // Inputs
    sensors__init();

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
    lcd_print_string_progmem(CONNECTING);
//    while(!password__changed__is_set());
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
