#include "main.c"

// BSP
#include "target/voltage-relay/bsp/buttons.c"
#include "target/voltage-relay/bsp/buzzer.c"
#include "target/voltage-relay/bsp/led_thread.c"
#include "target/voltage-relay/bsp/system_timer.c"
#include "target/voltage-relay/bsp/voltmeter.c"
#include "target/voltage-relay/bsp/zero_cross_detector.c"

// Library
#include "cpu/avr/util/bcd.c"
#include "cpu/avr/drivers/display/segment/glyphs__digits__decimal.c"
#include "cpu/avr/drivers/display/segment/number_renderer.c"
#include "cpu/avr/drivers/display/segment/dynamic3_thread.c"


