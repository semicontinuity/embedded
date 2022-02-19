#include "leds_backlight.h"
#include <avr/io.h>


#if defined(LEDS_BACKLIGHT__REFRESH__HOST) && defined(LEDS_BACKLIGHT__REFRESH__HOST)
DEFINE_BITVAR(leds_backlight__refresh, LEDS_BACKLIGHT__REFRESH__HOST, LEDS_BACKLIGHT__REFRESH__BIT);
#endif
