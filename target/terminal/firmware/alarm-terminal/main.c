#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#include "alarm_client.h"
#include "alarm_state.h"
#include "keypad.h"
#include "keypad_handler.h"
#include "led.h"

#include "lcd_backlight_service.h"
#include "state_change_pulse_transmitter.h"
#include "system_timer.h"

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"



const char MSG_READY[] PROGMEM = "\nГотов\n";
const char MSG_PASSWORD_NOT_ACCEPTED[] PROGMEM = "\nНеверный код\n";
const char MSG_PASSWORD_ACCEPTED[] PROGMEM = "\nКод принят\n";


// Implementation of callbacks
// ---------------------------

INLINE void keypad__on_event(const uint8_t keyevent) {
    keypad_handler__on_key_event(keyevent);
    lcd_backlight_service__signal();
}


INLINE void keypad_handler__on_password_char_typed(const uint8_t c) {
    terminal_displayChar('*');
}


INLINE void keypad_handler__on_incorrect_password(void) {
    lcd_print_string_progmem(MSG_PASSWORD_NOT_ACCEPTED);
}


INLINE void keypad_handler__on_correct_password(void) {
    lcd_print_string_progmem(MSG_PASSWORD_ACCEPTED);
    state_change_pulse_transmitter__signal();
}


INLINE void system_timer__on_system_tick(void) {       
    wdt_reset();

    keypad__run(); // contains delay!
    lcd_backlight_service__run();
    state_change_pulse_transmitter__run();
    alarm_client__run();
}


// RESET handler
// ---------------------------


int main(void) {
    wdt_enable (WDTO_2S);

    lcd_backlight_service__init();
    terminal_init();
    keypad__init();

    led__init();
    alarm_state__init();
    state_change_pulse_transmitter__init();
    alarm_client__init();


    system_timer__init();
    system_timer__start();

    lcd_print_string_progmem (MSG_READY);
    sei();
    return 0;
}
