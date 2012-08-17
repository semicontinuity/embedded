#include "device.h"
#include <avr/pgmspace.h>

#include "alarm.h"
#include "alarm_timer.h"


// device is "disarmed" - ignores all events from sensor
#define STATE_DISARMED      (0)

// valid password was entered, device ignores events from sensor for TIME_ARMING
#define STATE_ARMING        (1)

// device is "armed", actively watching sensor. 
#define STATE_ARMED         (2)

// Sensor was active when alarm is in state ARMED, that is, intruder was detected.
// If password is not entered during TIME_ALERT/timeAlert, alarm will turned on
#define STATE_ALERT         (3)

// valid password was not entered within TIME_ALERT. Alarm is turned on for TIME_ALARM
#define STATE_ALARM         (4)

// alarm was active for TIME_ALARM, now is muted for TIME_MUTE
// after TIME_MUTE time, device goes to STATE_ARMED state if there is no signal from sensor,
// or immediately again
#define STATE_MUTE_ALARM    (5)



unsigned char state;
unsigned char timeAlert;


void correctPasswordEntered (void) {
    if (state == STATE_DISARMED)
    {
        // If disarmed - arm
        alarm_state_armed();
        state = STATE_ARMING;
        alarm_timer__set(TIME_ARMING);
        timeAlert = TIME_ALERT;
    }
    else
    {
        // If not disarmed - disarm
        alarm_off(); // alarm may be on
        alarm_state_disarmed();
        // stop counting any timeouts for current state, STATE_DISARMED does not have timeout
        alarm_timer__reset(); 
        state = STATE_DISARMED;        
    }
}

// Called when some sensor has detected intruder
void sensor_signal(void) {
    if (state != STATE_ARMED) return;
    state = STATE_ALERT;
    alarm_timer__set(timeAlert);
}


void alarm_timer__output__run(void) {
    switch (state)
    {
    case STATE_ALARM:
        // ALARM is active for some time, let's mute it
        state = STATE_MUTE_ALARM;
        alarm_timer__set(TIME_MUTE);
        alarm_off();
        break;
    case STATE_MUTE_ALARM:
        // Muting period expired, switch to ARMED
        state = STATE_ARMED;
        alarm_timer__reset();
        timeAlert = TIME_ALERT_MUTE;
        // if sensors send alarm signal at this time, immediately fire alarm
        // (go thru STATE_ALERT state for technical reasons - after switch statement
        // it will be checked and actions to fire alarm will be taken
        // This should save 2 function calls = some flash memory)
        if (intruder_detected()) state = STATE_ALERT;
        break;
    case STATE_ARMING:
        // // Arming period ended, now we are ARMED
        state = STATE_ARMED;
        // if sensors send alarm signal at this time, immediately fire alarm
        // (go thru STATE_ALERT state for technical reasons - after switch statement
        // it will be checked and actions to fire alarm will be taken
        // This should save 2 function calls = some flash memory)

        // if an operator was late the alarm will be turned on immediately
        if (intruder_detected()) state = STATE_ALERT;


//        NB! fall thru deliberately (to save flash size)!
//        break;
//        NB! fall thru deliberately (to save flash size)!
//    case STATE_ALERT:
//        break;

// IF THERE IS A LACK OF MEMORY, goto STATEMENT CAN BE USED HERE
    }

    if (state == STATE_ALERT)
    {
        // Alert period ended, but alarm is not disarmed!
        // It is ALARM situation!
        state = STATE_ALARM;
        alarm_timer__set(TIME_ALARM);
        alarm_on();
        // actually, it means, ignore if were are muting alarm already
        if (timeAlert != TIME_ALERT_MUTE) 
        {
            alarm_notification();
        }
    }
}
    