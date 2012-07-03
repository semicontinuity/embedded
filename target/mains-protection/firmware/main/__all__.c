#include "main.c"

#include "cpu/avr/util/bcd.c"

#include "cpu/avr/drivers/display_segment_3_numeric.c"
#include "cpu/avr/drivers/display_segment_3_thread.c"

#include "platform/mains-protection/buttons.c"
#include "platform/mains-protection/buzzer.c"
#include "platform/mains-protection/led_thread.c"
#include "platform/mains-protection/system_timer.c"
#include "platform/mains-protection/voltmeter.c"
#include "platform/mains-protection/zero_cross_detector.c"

//#include "platform/mains-protection/frequency_counter.c"
