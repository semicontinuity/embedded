#include "device.h"
#include "keypad.h"
#include <stdint.h>

// The application must implement these callbacks
// ----------------------------------------------
void correctPasswordEntered(void);
void incorrectPasswordEntered(void);
void passwordCharTyped(uint8_t c);

// PASSWORD and PASSWORD_LENGTH are passwed during the build
char secretPassword[PASSWORD_LENGTH] = {PASSWORD};
char password[PASSWORD_LENGTH];
char enteredPasswordLength;


unsigned char passwordMatches(void) {
    if (enteredPasswordLength != PASSWORD_LENGTH) return 0;
    for (unsigned char i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (password[i] != secretPassword[i]) return 0;
    }
    return 1;
}



void passwordEntered(void) {
    if (!passwordMatches())
        incorrectPasswordEntered();
    else
        correctPasswordEntered();
}


void handlePasswordEntryEvent(uint8_t keyevent) {
    if (keyevent == KEYEVENT_POUND_PRESSED)
    {
        passwordEntered ();
        enteredPasswordLength = 0;
    }
    else if (enteredPasswordLength < PASSWORD_LENGTH
        && ((unsigned char)(keyevent & SCANMASK_PRESSED)) == SCANFLAG_PRESSED)
    {
        password[enteredPasswordLength++] = keyevent;
        passwordCharTyped(keyevent);
    }
}
 