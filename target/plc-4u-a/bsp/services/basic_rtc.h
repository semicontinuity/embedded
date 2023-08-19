#ifndef BASIC_RTC_H
#define BASIC_RTC_H

#include <stdint.h>


void basic_rtc__run(void);

void basic_rtc__on_minutes_timer_tick(void);

void basic_rtc__run_every_minute(void);


uint8_t basic_rtc__seconds__get(void);

uint8_t basic_rtc__minutes__get(void);

uint8_t basic_rtc__hours__get(void);

uint8_t basic_rtc__day_of_week_bits__get(void);


#endif
