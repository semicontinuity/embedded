// =============================================================================
// Keypad driver.
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


INLINE void keypad__run(void) {
    uint8_t scanMask = ~(1<<(KEYPAD__OUT__PIN));
    for (uint8_t column = 0; column < 4; column++)
    {
        keypad__out(scanMask);	// always pull up lower 4 lines (inputs)
        scanMask = ((uint8_t)(scanMask << 1)) | ((uint8_t)1);  // produce mask for the next column
        _delay_us(1);
        uint8_t scanValue = keypad__in();
        uint8_t changedLines = (uint8_t) (scanValue ^ keypad__state[column]);
        keypad__state[column] = scanValue;

        scanValue >>= KEYPAD__IN__PIN;
        changedLines >>= KEYPAD__IN__PIN;

        for (uint8_t row = 0; row < 4; row++)
        {
            if ((changedLines & 1) == 1)
            {
                // if lower bit of scanValue=1 => now key released; 0 => pressed
                uint8_t scancode = ROW(row) | COL(column);
#ifdef KEYPAD__ASCII_SCANCODES
                scancode = keypad__scancodes[scancode];
#endif

#ifdef KEYPAD__KEY_RELEASE_EVENTS
                if (scanValue & 1) {
                    scancode |= KEYPAD__EVENT__FLAG__RELEASED;
                }
                keypad__on_event(scancode);
#else
                if (!(scanValue & 1)) {
                    keypad__on_event(scancode);
                }
#endif                
            }
            scanValue >>= 1;
            changedLines >>= 1;
        }
    }
}
 