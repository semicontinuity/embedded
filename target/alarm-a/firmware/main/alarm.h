#ifndef __ALARM_H
#define __ALARM_H

enum alarm__state {
    // device is "disarmed" - ignores all events from sensor
    ALARM__STATE__DISARMED,

    // valid password was entered, device ignores events from sensor for TIME_ARMING
    ALARM__STATE__ARMING,

    // device is "armed", actively watching sensor. 
    ALARM__STATE__ARMED,

    // Sensor was active when alarm is in state ARMED, that is, intruder was detected.
    // If password is not until this state expires, alarm will be turned on.
    ALARM__STATE__ALERT,

    // valid password was not entered within TIME_ALERT. Alarm is turned on for TIME_ALARM
    ALARM__STATE__ALARM,

    // alarm was active for TIME_ALARM, now is muted for TIME_MUTE
    // after TIME_MUTE time, device goes to ALARM__STATE__ARMED state if there is no signal from sensor,
    // or immediately again
    ALARM__STATE__ALARM_MUTE,

    // device is "armed", actively watching sensor. 
    ALARM__STATE__ARMED_MUTE,

    // Sensor was active when alarm is in state ARMED_MUTE, that is, intruder was detected.
    // If password is not until this state expires, alarm will be turned on.
    ALARM__STATE__ALERT_MUTE
};

extern enum alarm__state alarm__state;

// Alarm API
void alarm__arm(void);
void alarm__disarm(void);
void alarm__sensor_active(void);

// Alarm callbacks - to be implemented by user
void alarm__out__run(void);
void alarm__sound__on(void);
void alarm__sound__off(void);

#endif
    