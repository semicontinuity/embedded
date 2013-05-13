// =============================================================================
// Keypad driver.
//
// Be extra careful trying to optimize this code.
// AVR-GCC may try to optimize the code, but instead can screw it up.
// This behaviour was observed for larger code size,
// approaching 16 Kb of flash.
// Something bad happens with temporary variables and/or shifts.
// =============================================================================
#include "drivers/keypad.h"
#include <stdint.h>
#include <util/delay.h>

static inline void keypad__out(const uint8_t v) { OUT(KEYPAD__OUT, v); }
static inline uint8_t keypad__in(void) { return IN(KEYPAD__IN); }

uint8_t keypad__state[] = {0xFF, 0xFF, 0xFF, 0xFF};


#ifdef KEYPAD__ASCII_SCANCODES
uint8_t keypad__scancodes[] = {
    '#', '0', '*', 'D',
    '9', '8', '7', 'C',
    '6', '5', '4', 'B',
    '3', '2', '1', 'A'
};
#endif

void keypad__scan_column(const uint8_t scanMask, const uint8_t column) __attribute__((noinline));
void keypad__scan_column(const uint8_t scanMask, const uint8_t column) {
    keypad__out(scanMask);
    _delay_loop_1(100); // small delay is necessary
    const uint8_t scanValue = keypad__in();
    uint8_t changedLines = (uint8_t) (scanValue ^ keypad__state[column]);
    keypad__state[column] = scanValue;        

    uint8_t tempScanValue = scanValue;
    tempScanValue >>= KEYPAD__IN__PIN;
    changedLines >>= KEYPAD__IN__PIN;
    const uint8_t scancode_column = COL(column);
    for (uint8_t row = 0; row < 4; row++) {
        if (changedLines & 1) {
            uint8_t scancode = ROW(row) | scancode_column;
#ifdef KEYPAD__ASCII_SCANCODES
            scancode = keypad__scancodes[scancode];
#endif

#ifdef KEYPAD__KEY_RELEASE_EVENTS
            if (tempScanValue & 1) {
                scancode |= KEYPAD__EVENT__FLAG__RELEASED;
            }
            keypad__on_event(scancode);
#else
            if (tempScanValue & 1) {
            }
            else {
                keypad__on_event(scancode);
            }
#endif                
        }
        tempScanValue >>= 1;
        changedLines >>= 1;
    }
}


INLINE void keypad__run(void) {
    keypad__scan_column(~(1<<(KEYPAD__OUT__PIN)), 0);
    keypad__scan_column(~(1<<(KEYPAD__OUT__PIN+1)), 1);
    keypad__scan_column(~(1<<(KEYPAD__OUT__PIN+2)), 2);
    keypad__scan_column(~(1<<(KEYPAD__OUT__PIN+3)), 3);
}
