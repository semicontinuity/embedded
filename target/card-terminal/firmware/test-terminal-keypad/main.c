#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"
#include "drivers/keypad.h"
#include "drivers/system_timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdint.h>


// =============================================================================
// Services binding
// =============================================================================

/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    DDRD |= (1<<0);
    PORTD |= (1<<0);

    keypad__run();
}

void keypad__on_event(const uint8_t keyevent) {
    terminal__putc(keyevent);
}

// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Drivers
    LCDG_InitPort();
    _delay_ms(30);
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

    terminal__init();
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
    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    application__init();
    application__start();

    sei();
    for(;;);
    return 0;
}
