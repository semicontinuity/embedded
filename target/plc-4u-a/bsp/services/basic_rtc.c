// =============================================================================
// Basic RTC
//
// Real time is maintained in 2 holding registers:
// HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS
// - lo byte: seconds
// - hi byte: minutes
// HOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH
// - lo byte: hours (0-23)
// - hi byte: dat of week, bit 0 = Sunday, .. bit 6 = Saturday
//
// Day of week is a bit mask for convenience,
// to create bit-mask based rules.
//
// Adjusting RTC is only possible via MODBUS.
// Since DOW bits are not set at startup,
// they will not be updated, until set appropriately via MODBUS.
// =============================================================================

#include "services/holding_registers.h"
#include "services/basic_rtc.h"


/** Must be invoked on every tick of the minutes timer */
void basic_rtc__run_every_minute(void) {
    uint8_t minutes = holding_registers__buffer__get_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
    ++minutes;
    if (minutes == 60) {
        minutes = 0;

        uint8_t hours = holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH);
        ++hours;
        if (hours == 24) {
            hours = 0;

            uint8_t dow = holding_registers__buffer__get_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH);
            dow <<= 1;
            if (dow == 0x80) {
                dow = 0x01;
            }

            holding_registers__buffer__set_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH, dow);
        }

        holding_registers__buffer__set_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH, hours);
    }

    holding_registers__buffer__set_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS, minutes);
}


/** Must be invoked on every tick of the seconds timer */
void basic_rtc__run(void) {
    uint8_t seconds = holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
    ++seconds;
    if (seconds == 60) {
        seconds = 0;
        basic_rtc__on_minutes_timer_tick();
    }
    holding_registers__buffer__set_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS, seconds);
}

uint8_t basic_rtc__get_seconds(void) {
    return holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
}

uint8_t basic_rtc__get_minutes(void) {
    return holding_registers__buffer__get_u8_hi(HOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS);
}
