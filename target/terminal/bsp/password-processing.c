#include <avr/pgmspace.h>
#include "keyboard-scanner.h"


//char SCAN2ASCII[] = {
//    'D', 'C', 'B', 'A', '*', '7', '4', '1', '0', '8', '5', '2', '#', '9', '6', '3'
//};


#define PASSWORD_LENGTH         (8)
char secretPassword[PASSWORD_LENGTH] = {
        KEYEVENT_7_PRESSED,
        KEYEVENT_7_PRESSED,
        KEYEVENT_2_PRESSED,
        KEYEVENT_0_PRESSED,
        KEYEVENT_0_PRESSED,
        KEYEVENT_1_PRESSED,
        KEYEVENT_7_PRESSED,
        KEYEVENT_9_PRESSED
};

char password[PASSWORD_LENGTH];
char enteredPasswordLength;


unsigned char passwordMatches (void)
{
    if (enteredPasswordLength != PASSWORD_LENGTH) return 0;
    for (unsigned char i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (password[i] != secretPassword[i]) return 0;
    }
//    print('Y');
    return 1;
}

void correctPasswordEntered (void);
void incorrectPasswordEntered (void);
void passwordCharTyped(uint8_t c);

void passwordEntered (void)
{
//    print('?');
    if (!passwordMatches ())
        incorrectPasswordEntered();
    else
        correctPasswordEntered();
}

void handlePasswordEntryEvent (uint8_t keyevent)
{
//    print (SCAN2ASCII[keyevent>>1]);
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
 