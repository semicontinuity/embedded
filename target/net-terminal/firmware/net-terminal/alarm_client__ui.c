#include "alarm_client__auth.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"
#include <stdint.h>


char alarm_client__ui__entered_password[8];
int  alarm_client__ui__entered_password_length;

const char MSG_PASSWORD_NOT_ACCEPTED[] PROGMEM = "\nНеверный код\n";


// The application must implement these callbacks
// ----------------------------------------------
INLINE void alarm_client__ui__on_correct_password(void) {
}

INLINE void alarm_client__ui__on_incorrect_password(void) {
    lcd_print_string_progmem(MSG_PASSWORD_NOT_ACCEPTED);
}

inline void alarm_client__ui__on_password_char_typed(const uint8_t c) {
    terminal_displayChar('*');
}

inline unsigned char alarm_client__ui__password_matches(void) {
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
 