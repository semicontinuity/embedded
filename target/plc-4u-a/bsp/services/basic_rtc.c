#include <stdint.h>
#include "services/holding_registers.h"
#include "services/basic_rtc.h"


/** Must be invoked on every tick of the seconds timer */
void basic_rtc__run(void) {
    uint8_t seconds = holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
    ++seconds;
    if (seconds == 60) {
        seconds = 0;

        uint16_t minutes = holding_registers__buffer__get_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
        ++minutes;
        if (minutes == 60) {
            minutes = 0;
        }

        holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS, minutes);
    }
    holding_registers__buffer__set_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS, seconds);
}
