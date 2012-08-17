#include "keypad.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#define KEYBOARD_SCAN_DELAY (F_CPU/100000)


#define COL0_SCAN_MASK      (~_BV(4) & 0xFF)
#define COL1_SCAN_MASK      (~_BV(5) & 0xFF)
#define COL2_SCAN_MASK      (~_BV(6) & 0xFF)
#define COL3_SCAN_MASK      (~_BV(7) & 0xFF)


#define outputScanValue(v)  OUT(KEYPAD, (v))
#define inputScanValue()    IN(KEYPAD)



/** An application must define this event handler */
void keypad__on_event(uint8_t keyevent);


char keyboardState[] = {-1, -1, -1, -1};


INLINE void keypad__run(void) {
    uint8_t scanMask = COL0_SCAN_MASK;
    for (uint8_t column = 0; column < 4; column++)
    {
        outputScanValue (scanMask);	// always pull up lower 4 lines (inputs)
        scanMask = ((uint8_t)(scanMask << 1)) | ((uint8_t)1);
       _delay_loop_1(KEYBOARD_SCAN_DELAY);

//DDRB=0; // all inputs (temporary - will avoid collisions?)
//PORTB=scanMask;
//DDRB=(~scanMask)&0xF0; // lower bits always 0 (input)
        uint8_t scanValue = inputScanValue ();
        uint8_t tempScanValue = scanValue;
        uint8_t changedLines = (uint8_t) (scanValue ^ keyboardState[column]);
        for (uint8_t row = 0; row < 4; row++)
        {
            if ((changedLines & 1) == 1)
            {
//                print('~');
//                print(96+column);
//                print(96+row);
//                print(96+(scanMask>>4));
                // if lower bit of tempScanValue=1 => now key released; 0 => pressed
                uint8_t scancode =
                    (uint8_t) ((tempScanValue & 1) | ROW(row) | COL(column));
                keypad__on_event(scancode);
            }
            tempScanValue >>= 1;
            changedLines >>= 1;
        }
        keyboardState[column] = scanValue;        
    }
}
 