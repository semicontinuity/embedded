#include "keypad.h"
#include <stdint.h>

// The application must implement these callbacks
// ----------------------------------------------
void keypad_handler__on_correct_password(void);
void keypad_handler__on_incorrect_password(void);
void keypad_handler__on_password_char_typed(uint8_t c);

// PASSWORD and PASSWORD_LENGTH are passwed during the build
char keypad_handler__password[PASSWORD_LENGTH] = {PASSWORD};
char keypad_handler__entered_password[PASSWORD_LENGTH];
int  keypad_handler__entered_password_length;


inline unsigned char keypad_handler__password_matches(void) {
    if (keypad_handler__entered_password_length != PASSWORD_LENGTH) return 0;
    for (unsigned char i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (keypad_handler__entered_password[i] != keypad_handler__password[i]) return 0;
    }
    return 1;
}


inline void keypad_handler__on_password_entered(void) {
    if (!keypad_handler__password_matches())
        keypad_handler__on_incorrect_password();
    else
        keypad_handler__on_correct_password();
}


INLINE void keypad_handler__on_key_event(uint8_t keyevent) {
    if (keyevent == KEYEVENT_POUND_PRESSED)
    {
        keypad_handler__on_password_entered();
        keypad_handler__entered_password_length = 0;
    }
    else if (keypad_handler__entered_password_length < PASSWORD_LENGTH
        && ((unsigned char)(keyevent & SCANMASK_PRESSED)) == SCANFLAG_PRESSED)
    {
        keypad_handler__entered_password[keypad_handler__entered_password_length++] = keyevent;
        keypad_handler__on_password_char_typed(keyevent);
    }
}
 