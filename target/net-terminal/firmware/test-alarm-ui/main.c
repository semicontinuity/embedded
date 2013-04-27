#include "cpu/avr/drivers/display/mt12864/terminal.h"

#include "drivers/out/lcd_backlight.h"
#include "drivers/keypad.h"
#include "drivers/system_timer.h"

#include "flags/alarm__state__changed.h"


#include "alarm_client__auth.h"
#include "alarm_client__state.h"
#include "alarm_client__ui.h"

#include "services/lcd_backlight_fader.h"
#include "services/lcd_backlight_service.h"

#include <avr/interrupt.h>


#include "can_selector.h"
#include "cpu/avr/spi.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"


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
}

void keypad__on_event(const uint8_t keyevent) {
    lcd_backlight_service__signal();
    alarm_client__ui__on_key_event(keyevent);
}


INLINE void alarm_client__state__on_changed(void) {
    alarm_client__ui__on_state_changed();
}


INLINE void alarm_client__new_state__on_changed(void) {
    alarm_client__state = alarm_client__new_state;
    alarm_client__state__on_changed();
}


INLINE void alarm_client__auth__password__on_invalidated(void) {
}


INLINE void alarm_client__state__on_invalidated(void) {
}


// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Outputs
    lcd_backlight__init();

    // Flags
    alarm__state__changed__init();

    // Drivers
    system_timer__init();

    // Services
    keypad__init();
    terminal_init();
}


inline static void application__start(void) {
    alarm_client__auth__password.length = 4;
    alarm_client__auth__password.data[0] = 'A';
    alarm_client__auth__password.data[1] = 'B';
    alarm_client__auth__password.data[2] = 'C';
    alarm_client__auth__password.data[3] = 'D';

    system_timer__start();
}

inline static void application__stop(void) {
    system_timer__stop();
}


// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    spi__init(SPI_CLKDIV_4);
    spi__double_speed__set(1);
    can_selector__init();
    mcp251x__init();

    application__init();
    application__start();

    sei();
    for(;;);
    return 0;
}
