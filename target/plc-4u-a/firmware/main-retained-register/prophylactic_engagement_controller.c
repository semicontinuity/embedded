#include "prophylactic_engagement_controller.h"
#include <services/basic_rtc.h>
#include <services/holding_registers.h>
#include "valve_controller__1.h"


// Configuration
// -----------------------------------------------------------------------------

bool prophylactic_engagement_controller__enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__PROPHYLACTIC_ENGAGEMENT__ENABLED);
}

uint16_t prophylactic_engagement_controller__delay_minutes__get(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__PROPHYLACTIC_ENGAGEMENT__DELAY_MINUTES);
}

uint8_t prophylactic_engagement_controller__day_of_week_mask__get(void) {
    return holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__PROPHYLACTIC_ENGAGEMENT__DOW_MASK);
}

uint8_t prophylactic_engagement_controller__hours__get(void) {
    return holding_registers__buffer__get_u8_hi(HOLDING_REGISTER__ADDRESS__PROPHYLACTIC_ENGAGEMENT__TIME_HH_MM);
}

uint8_t prophylactic_engagement_controller__minutes__get(void) {
    return holding_registers__buffer__get_u8_lo(HOLDING_REGISTER__ADDRESS__PROPHYLACTIC_ENGAGEMENT__TIME_HH_MM);
}


// Logic
// -----------------------------------------------------------------------------

// run every minute
void prophylactic_engagement_controller__do_run(void) {
}


// run every minute
void prophylactic_engagement_controller__run(void) {
    if (prophylactic_engagement_controller__enabled()) {
        if (basic_rtc__day_of_week_bits__get() & prophylactic_engagement_controller__day_of_week_mask__get()) {
            if (valve_controller__1__idle_time_minutes__get() > prophylactic_engagement_controller__delay_minutes__get()) {
                if (basic_rtc__hours__get() == prophylactic_engagement_controller__hours__get()) {
                    if (basic_rtc__minutes__get() == prophylactic_engagement_controller__minutes__get()) {
                        prophylactic_engagement_controller__do_run();
                    }
                }
            }
        }
    }
}
