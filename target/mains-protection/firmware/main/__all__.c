#include "main.c"

// BSP
#include "target/mains-protection/bsp/buttons.c"
#include "target/mains-protection/bsp/buzzer.c"
#include "target/mains-protection/bsp/led_thread.c"
#include "target/mains-protection/bsp/system_timer.c"
#include "target/mains-protection/bsp/voltmeter.c"
#include "target/mains-protection/bsp/zero_cross_detector.c"

// Library
#include "cpu/avr/util/bcd.c"
#include "cpu/avr/drivers/display/segment/dynamic3_numeric.c"
#include "cpu/avr/drivers/display/segment/dynamic3_thread.c"


