#include "prophylactic_engagement_controller.h"
#include <services/basic_rtc.h>
#include <services/holding_registers.h>
#include <services/coils.h>
#include "valve_controller__1.h"
#include "alert_controller.h"


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


// State
// -----------------------------------------------------------------------------

void prophylactic_engagement_controller__requested__set(bool value) {
    coils__set(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__REQUESTED, value);
}

bool prophylactic_engagement_controller__requested__get(void) {
    return coils__get(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__REQUESTED);
}


void prophylactic_engagement_controller__phase_1__running__set(bool value) {
    coils__set(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__PHASE_1__RUNNING, value);
}

bool prophylactic_engagement_controller__phase_1__running__get(void) {
    return coils__get(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__PHASE_1__RUNNING);
}


void prophylactic_engagement_controller__phase_2__running__set(bool value) {
    coils__set(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__PHASE_2__RUNNING, value);
}

bool prophylactic_engagement_controller__phase_2__running__get(void) {
    return coils__get(INTERNAL_COIL__PROPHYLACTIC_ENGAGEMENT__PHASE_2__RUNNING);
}


// Logic
// -----------------------------------------------------------------------------

// run every second
void prophylactic_engagement_controller__on_seconds_timer_tick(void) {
    if (prophylactic_engagement_controller__phase_1__running__get()) {
        valve_controller__1__try_toggle();
    } else if (prophylactic_engagement_controller__phase_2__running__get()) {

    } else if (prophylactic_engagement_controller__requested__get()) {
        if (alert_controller__has_water_alerts()) {
            alerting__failure__prophylactic_engagement_controller__push(true);
            prophylactic_engagement_controller__requested__set(false);
        } else {
            prophylactic_engagement_controller__phase_1__running__set(true);
        }
    }
}


// run every minute
void prophylactic_engagement_controller__on_minutes_timer_tick(void) {
    if (prophylactic_engagement_controller__enabled()) {
        if (basic_rtc__day_of_week_bits__get() & prophylactic_engagement_controller__day_of_week_mask__get()) {
            if (valve_controller__1__idle_time_minutes__get() > prophylactic_engagement_controller__delay_minutes__get()) {
                if (basic_rtc__hours__get() == prophylactic_engagement_controller__hours__get()) {
                    if (basic_rtc__minutes__get() == prophylactic_engagement_controller__minutes__get()) {
                        prophylactic_engagement_controller__requested__set(true);
                    }
                }
            }
        }
    }
}
