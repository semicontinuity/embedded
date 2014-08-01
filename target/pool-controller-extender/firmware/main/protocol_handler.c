// =============================================================================
// Error-tolerant UART protocol handler
// Protocol:
// The only supported command is SET BUTTONS TAO (simulate button event)
//
// Every event is coded in two bytes:
// 1st byte: 00XXXXXX, where XXXXXX is the bit mask of buttons pressed.
// 2nd byte: 11XXXXXX, where XXXXXX is the bit mask of buttons pressed.
// the bit masks in these two bytes must be the same, otherwise it's an error.
//
// Alarm output line is used for debug purposes.
// WDT is
// =============================================================================

#include "drivers/io/buttons_tap.h"
#include "drivers/out/alarm.h"
#include <avr/io.h>
#include <avr/wdt.h>

// chip specific!
void wdt__disable_unsafe(void) {
    __asm__ __volatile__ (  \
        "sts %0, %1"            "\n\t" \
        "sts %0, __zero_reg__"  "\n\t" \
        : /* no outputs */ \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))) \
    );
}

// chip specific!
void wdt__enable_unsafe(const uint8_t value) {
    __asm__ __volatile__ (  \
        "sts %0,%1" "\n\t"  \
        "sts %0,%2" "\n\t"  \
        : /* no outputs */  \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))), \
        "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDE) | (value & 0x07)) ) \
    );
}

void wdt__reset(void) {
    __asm__ __volatile__ ("wdr");
}


#ifdef PROTOCOL_HANDLER__LAST__REG
register uint8_t protocol_handler__last asm(QUOTE(PROTOCOL_HANDLER__LAST__REG));
#else
volatile uint8_t protocol_handler__last;
#endif


void protocol_handler__accept(uint8_t value) {
    if (value & 0xC0) {
        // erroneous byte or second byte
        if ((protocol_handler__last ^ value) == 0xC0) {
            // conforms to protocol
            alarm__set(1);
            if (protocol_handler__last) {
                // simulate press of at least one of the buttons
                // button release even should arrive within 8s, otherwise system will be endlessly reset by WDT.
                wdt__reset();
                wdt__enable_unsafe(WDTO_8S);
            }
            else {
                // no buttons pressed
                wdt__disable_unsafe();
            }
        }
        else {
            // protocol error
            alarm__set(0);
        }
        protocol_handler__last = 0;
    }
    else {
        // first byte (0b00XXXXXX)
        protocol_handler__last = value;
        alarm__set(0);
    }
}
