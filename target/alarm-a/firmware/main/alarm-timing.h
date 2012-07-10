#ifndef __ALARM_TIMING_H
#define __ALARM_TIMING_H

// NB - all times cannot exceed 255!

#define TIME_ARMING         (120)

// Time to stay in ALERT state after intruder has been detected.
// must be >0 because it is decremented before check
#define TIME_ALERT_MUTE     (1)
#define TIME_ALERT          (120)
#define TIME_MUTE           (180)
#define TIME_ALARM          (60)

#endif


