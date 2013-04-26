#include "alarm_client__auth.h"
#include "alarm_client__state.h"
#include "alarm_client__ui.h"
#include "drivers/out/led.h"
#include "flags/password__changed.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"
#include <stdint.h>


uint8_t alarm_client__ui__entered_password[8];
uint8_t alarm_client__ui__entered_password_length;

const char ALARM_CLIENT__UI__MSG_ARMED[] PROGMEM = "\n\n\nПоставлено на охрану\n\nДля снятия с охраны\nвведите код\n\n";
const char ALARM_CLIENT__UI__MSG_DISARMED[] PROGMEM = "\n\n\nСнято с охраны\n\nДля постановки\nна охрану введите код\n\n";


INLINE void alarm_client__ui__start(void) {
    terminal_displayChar('.');
    alarm_client__auth__password__invalidate();
    terminal_displayChar('.');
    while (!password__changed__is_set());
    terminal_displayChar('.');
    alarm_client__state__invalidate();
    terminal_displayChar('.');
}


void alarm_client__ui__display_state(void) {
    const char * PROGMEM message;
    if (alarm_client__state) {
        led__on();
        message = ALARM_CLIENT__UI__MSG_ARMED;
    }
    else {
        led__off();
        message = ALARM_CLIENT__UI__MSG_DISARMED;
    }
    lcd_print_string_progmem(message);
}


INLINE void alarm_client__ui__on_correct_password(void) {
    alarm_client__server_state__set(!alarm_client__state);
}

INLINE void alarm_client__ui__on_incorrect_password(void) {
    alarm_client__ui__display_state();
}

INLINE void alarm_client__ui__on_password_char_typed(const uint8_t c) {
    terminal_displayChar('*');
}

INLINE void alarm_client__ui__on_state_changed(void) {
    alarm_client__ui__entered_password_length = 0;
    alarm_client__ui__display_state();
}

INLINE unsigned char alarm_client__ui__password_matches(void) {
    if (alarm_client__ui__entered_password_length != alarm_client__auth__password.length) return 0;
    for (unsigned char i = 0; i < alarm_client__auth__password.length; i++) {
        if (alarm_client__ui__entered_password[i] != alarm_client__auth__password.data[i]) return 0;
    }
    return 1;
}


INLINE void alarm_client__ui__on_password_entered(void) {
    if (!alarm_client__ui__password_matches())
        alarm_client__ui__on_incorrect_password();
    else
        alarm_client__ui__on_correct_password();
}


INLINE void alarm_client__ui__on_key_event(const uint8_t keyevent) {
    if (keyevent == '#') {
        alarm_client__ui__on_password_entered();
        alarm_client__ui__entered_password_length = 0;
    }
    else if (alarm_client__ui__entered_password_length < sizeof(alarm_client__ui__entered_password))
    {
        alarm_client__ui__entered_password[alarm_client__ui__entered_password_length++] = keyevent;
        alarm_client__ui__on_password_char_typed(keyevent);
    }
}
 