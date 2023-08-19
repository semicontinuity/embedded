#ifndef BASIC_RTC_H
#define BASIC_RTC_H

#include <stdint.h>


void basic_rtc__run(void);

void basic_rtc__on_minutes_timer_tick(void);

void basic_rtc__run_every_minute(void);


uint8_t basic_rtc__get_seconds(void);

uint8_t basic_rtc__get_minutes(void);

#endif
