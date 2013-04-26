#include "alarm.h"
#include "alarm_timer.h"


uint8_t EEMEM ee__alarm__time_arming     = ALARM__TIME_ARMING;
uint8_t EEMEM ee__alarm__time_alert      = ALARM__TIME_ALERT;
uint8_t EEMEM ee__alarm__time_alert_mute = ALARM__TIME_ALERT_MUTE;
uint8_t EEMEM ee__alarm__time_alarm      = ALARM__TIME_ALARM;
uint8_t EEMEM ee__alarm__time_alarm_mute = ALARM__TIME_ALARM_MUTE;

uint8_t alarm__time_arming;
uint8_t alarm__time_alert;
uint8_t alarm__time_alert_mute;
uint8_t alarm__time_alarm;
uint8_t alarm__time_alarm_mute;

enum alarm__state alarm__state;

/**
 * Arm the alarm.
 * The alarm state should be broadcasted at the call site.
 */
void alarm__arm(void) {
    alarm__state = ALARM__STATE__ARMING;
    alarm_timer__set(alarm__time_arming);
}


/**
 * Disarm the alarm.
 * The alarm state should be broadcasted at the call site.
 */
void alarm__disarm(void) {
    alarm__sound__off(); // alarm may be on
    alarm__state = ALARM__STATE__DISARMED;
    // stop counting any timeouts for current state, ALARM__STATE__DISARMED does not have timeout
    alarm_timer__reset(); 
}


static inline void alarm__state__set(const uint8_t state) {
    alarm__state = state;
    alarm__state__on_change();
}



// Called when some sensor has detected an intruder
void alarm__sensor_active(void) {
    if (alarm__state == ALARM__STATE__ARMED) {
        alarm__state__set(ALARM__STATE__ALERT);
        alarm_timer__set(alarm__time_alert);
    }
    else if (alarm__state == ALARM__STATE__ARMED_MUTE) {
        alarm__state__set(ALARM__STATE__ALERT_MUTE);
        alarm_timer__set(alarm__time_alert_mute);
    }
    // ignore in other states
}


// Called when alarm timer has expired
void alarm_timer__output__run(void) {
    switch (alarm__state)
    {
    case ALARM__STATE__ARMING:
        // Arming period ended, now we are ARMED
        alarm__state__set(ALARM__STATE__ARMED);
        break;
    case ALARM__STATE__ALERT:
        // Alert time expired, switching to ALARM state.
        alarm__out__run();
        // fall thru to switch to ALARM state
    case ALARM__STATE__ALERT_MUTE:
        // Alert time expired, switching to ALARM state.
        alarm__state__set(ALARM__STATE__ALARM);
        alarm_timer__set(alarm__time_alarm);
        alarm__sound__on();
        break;
    case ALARM__STATE__ALARM:
        // ALARM state has expired, let's mute the sound and switch to ALARM_MUTE state.
        alarm__sound__off();
        alarm__state__set(ALARM__STATE__ALARM_MUTE);
        alarm_timer__set(alarm__time_alarm_mute);
        break;
    case ALARM__STATE__ALARM_MUTE:
        // Muting period expired, switch to ARMED_MUTE
        alarm__state__set(ALARM__STATE__ARMED_MUTE);
        break;
    case ALARM__STATE__DISARMED:
    case ALARM__STATE__ARMED:
    case ALARM__STATE__ARMED_MUTE:
        // alarm timer is stopped in these states, so will never get here.
        break;
    }
}
