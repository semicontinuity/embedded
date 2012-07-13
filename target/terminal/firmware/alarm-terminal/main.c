#include "device.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#include "alarm_client.h"
#include "keypad.h"
#include "password-processing.h"
#include "lcd_backlight_service.h"

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"



const char MSG_READY[] PROGMEM = "\nГотов\n";
const char MSG_PASSWORD_NOT_ACCEPTED[] PROGMEM = "\nНеверный код\n";
const char MSG_PASSWORD_ACCEPTED[] PROGMEM = "\nКод принят\n";



uint8_t stateChangePulseTimeout;


void state_change_pulse_start(void) {
    state_change_low();
    stateChangePulseTimeout = 100;
}


void state_change_pulse_run(void) {
    if (stateChangePulseTimeout != 0) // generating pulse
    {
        --stateChangePulseTimeout;
        if (stateChangePulseTimeout == 0) // just reached 0 - pulse generated
        {
            state_change_high();
        }
    }
}


void keyEvent(const uint8_t keyevent) {
    handlePasswordEntryEvent (keyevent);
    lcd_backlight_service__signal();
}


void passwordCharTyped(const uint8_t c) {
    terminal_displayChar('*');
}


void incorrectPasswordEntered(void) {
    lcd_print_string_progmem(MSG_PASSWORD_NOT_ACCEPTED);
}


void correctPasswordEntered(void) {
    lcd_print_string_progmem(MSG_PASSWORD_ACCEPTED);
    state_change_pulse_start();
}


/**
 * This interrupt is invoked F_CPU/1024/256 times per second.
 * (e.g. 45.5 / sec @ 12 MHz)
 */
ISR(PERIODIC_INTERRUPT_VECT)
{       
    wdt_reset();

    keypad__run(); // contains delay!
    lcd_backlight_service__run();
    state_change_pulse_run();
    alarm_client__run();
}


int main(void) {
    wdt_enable (WDTO_2S);

    lcd_backlight_service__init();
    terminal_init();
    keypad__init();

    configure_io();
    alarm_client__init();

    init_and_start_scheduler();


    lcd_print_string_progmem (MSG_READY);
    sei();
    return 0;
}
