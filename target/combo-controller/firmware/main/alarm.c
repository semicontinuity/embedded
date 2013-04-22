#include "alarm.h"
#include "alarm_timer.h"


enum alarm__state alarm__state;


void alarm__arm(void) {
    alarm__state = ALARM__STATE__ARMING;
    alarm_timer__set(ALARM__TIME_ARMING);
}


void alarm__disarm(void) {
    alarm__sound__off(); // alarm may be on
    alarm__state = ALARM__STATE__DISARMED;
    // stop counting any timeouts for current state, ALARM__STATE__DISARMED does not have timeout
    alarm_timer__reset(); 
}



// Called when some sensor has detected an intruder
void alarm__sensor_active(void) {
    if (alarm__state == ALARM__STATE__ARMED) {
        alarm__state = ALARM__STATE__ALERT;
        alarm_timer__set(ALARM__TIME_ALERT);
    }
    else if (alarm__state == ALARM__STATE__ARMED_MUTE) {
        alarm__state = ALARM__STATE__ALERT_MUTE;
        alarm_timer__set(ALARM__TIME_ALERT_MUTE);
    }
    // ignore in other states
}


// Called when alarm timer has expired
void alarm_timer__output__run(void) {
    switch (alarm__state)
    {
    case ALARM__STATE__ARMING:
        // Arming period ended, now we are ARMED
        alarm__state = ALARM__STATE__ARMED;
        break;
    case ALARM__STATE__ALERT:
        // Alert time expired, switching to ALARM state.
        alarm__out__run();
        // fall thru to switch to ALARM state
    case ALARM__STATE__ALERT_MUTE:
        // Alert time expired, switching to ALARM state.
        alarm__state = ALARM__STATE__ALARM;
        alarm_timer__set(ALARM__TIME_ALARM);
        alarm__sound__on();
        break;
    case ALARM__STATE__ALARM:
        // ALARM state has expired, let's mute the sound and switch to ALARM_MUTE state.
        alarm__sound__off();
        alarm__state = ALARM__STATE__ALARM_MUTE;
        alarm_timer__set(ALARM__TIME_ALARM_MUTE);
        break;
    case ALARM__STATE__ALARM_MUTE:
        // Muting period expired, switch to ARMED_MUTE
        alarm__state = ALARM__STATE__ARMED_MUTE;
        break;
    case ALARM__STATE__DISARMED:
    case ALARM__STATE__ARMED:
    case ALARM__STATE__ARMED_MUTE:
        // alarm timer is stopped in these states, so will never get here.
        break;
    }

}
