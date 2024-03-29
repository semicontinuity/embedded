#ifndef LEDS_BACKLIGHT_H
#define LEDS_BACKLIGHT_H

#include "util/bitops.h"
#include <services/gp_buffer.h>


#if defined(LEDS_BACKLIGHT__REFRESH__HOST) && defined(LEDS_BACKLIGHT__REFRESH__HOST)
DECLARE_BITVAR(leds_backlight__refresh);
#endif


void leds_backlight__init(void);

bool leds_backlight__refresh__thread__is_runnable(void);

void leds_backlight__refresh__thread__run(void);


#endif
