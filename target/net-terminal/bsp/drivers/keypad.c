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
static inline uint8_t keypad__in(void) { return PORT_VALUE(KEYPAD__IN); }

uint8_t keypad__state[] = {0xFF, 0xFF, 0xFF, 0xFF};


#ifdef KEYPAD__ASCII_SCANCODES
uint8_t keypad__scancodes[] = {
    '#', '0', '*', 'D',
    '9', '8', '7', 'C',
    '6', '5', '4', 'B',
    '3', '2', '1', 'A'
};
#endif


INLINE void keypad__run(void) {
    uint8_t scanMask = ~(1<<(KEYPAD__OUT__PIN));
    for (uint8_t column = 0; column < 4; column++) {
        keypad__out(scanMask);	// always pull up lower 4 lines (inputs)
        scanMask = ((uint8_t)(scanMask << 1)) | ((uint8_t)1);
        _delay_loop_1(100); // small delay is necessary
        uint8_t scanValue = keypad__in();
        uint8_t tempScanValue = scanValue;
        uint8_t changedLines = (uint8_t) (scanValue ^ keypad__state[column]);


        tempScanValue >>= KEYPAD__IN__PIN;
        changedLines >>= KEYPAD__IN__PIN;
        const uint8_t scancode_column = COL(column);
        for (uint8_t row = 0; row < 4; row++) {
            if ((changedLines & 1) == 1) {
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
        keypad__state[column] = scanValue;        
    }
}
