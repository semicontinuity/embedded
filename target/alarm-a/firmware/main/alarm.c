#include "in_sensor_line.h"
#include "out_alarm_state_line.h"
#include "alarm.h"
#include "alarm_timer.h"


// device is "disarmed" - ignores all events from sensor
#define ALARM__STATE__DISARMED      (0)

// valid password was entered, device ignores events from sensor for TIME_ARMING
#define ALARM__STATE__ARMING        (1)

// device is "armed", actively watching sensor. 
#define ALARM__STATE__ARMED         (2)

// Sensor was active when alarm is in state ARMED, that is, intruder was detected.
// If password is not entered during TIME_ALERT/alarm__time_alert, alarm will turned on
#define ALARM__STATE__ALERT         (3)

// valid password was not entered within TIME_ALERT. Alarm is turned on for TIME_ALARM
#define ALARM__STATE__ALARM         (4)

// alarm was active for TIME_ALARM, now is muted for TIME_MUTE
// after TIME_MUTE time, device goes to ALARM__STATE__ARMED state if there is no signal from sensor,
// or immediately again
#define ALARM__STATE__MUTE_ALARM    (5)



unsigned char alarm__state;
unsigned char alarm__time_alert;


void alarm__correct_password_entered(void) {
    if (alarm__state == ALARM__STATE__DISARMED) {
        // If disarmed - arm
        alarm_state_line__on();
        alarm__state = ALARM__STATE__ARMING;
        alarm_timer__set(TIME_ARMING);
        alarm__time_alert = TIME_ALERT;
    }
    else {
        // If not disarmed - disarm
        alarm__sound__off(); // alarm may be on
        alarm_state_line__off();
        // stop counting any timeouts for current state, ALARM__STATE__DISARMED does not have timeout
        alarm_timer__reset(); 
        alarm__state = ALARM__STATE__DISARMED;        
    }
}

// Called when some sensor has detected intruder
void alarm__sensor_active(void) {
    if (alarm__state != ALARM__STATE__ARMED) return;
    alarm__state = ALARM__STATE__ALERT;
    alarm_timer__set(alarm__time_alert);
}


void alarm_timer__output__run(void) {
    switch (alarm__state)
    {
    case ALARM__STATE__ALARM:
        // ALARM is active for some time, let's mute it
        alarm__state = ALARM__STATE__MUTE_ALARM;
        alarm_timer__set(TIME_MUTE);
        alarm__sound__off();
        break;
    case ALARM__STATE__MUTE_ALARM:
        // Muting period expired, switch to ARMED
        alarm__state = ALARM__STATE__ARMED;
        alarm_timer__reset();
        alarm__time_alert = TIME_ALERT_MUTE;
        // if sensors send alarm signal at this time, immediately fire alarm
        // (go thru ALARM__STATE__ALERT state for technical reasons - after switch statement
        // it will be checked and actions to fire alarm will be taken
        // This should save 2 function calls = some flash memory)
        if (sensor_line__is_active()) alarm__state = ALARM__STATE__ALERT;
        break;
    case ALARM__STATE__ARMING:
        // // Arming period ended, now we are ARMED
        alarm__state = ALARM__STATE__ARMED;
        // if sensors send alarm signal at this time, immediately fire alarm
        // (go thru ALARM__STATE__ALERT state for technical reasons - after switch statement
        // it will be checked and actions to fire alarm will be taken
        // This should save 2 function calls = some flash memory)

        // if an operator was late the alarm will be turned on immediately
        if (sensor_line__is_active()) alarm__state = ALARM__STATE__ALERT;


//        NB! fall thru deliberately (to save flash size)!
//        break;
//        NB! fall thru deliberately (to save flash size)!
//    case ALARM__STATE__ALERT:
//        break;

// IF THERE IS A LACK OF MEMORY, goto STATEMENT CAN BE USED HERE
    }

    if (alarm__state == ALARM__STATE__ALERT) {
        // Alert period ended, but alarm is not disarmed!
        // It is ALARM situation!
        alarm__state = ALARM__STATE__ALARM;
        alarm_timer__set(TIME_ALARM);
        alarm__sound__on();
        // actually, it means, ignore if were are muting alarm already
        if (alarm__time_alert != TIME_ALERT_MUTE) {
            alarm__out__run();
        }
    }
}
