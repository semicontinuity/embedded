// LEDs
#include "leds.c"
#include "drivers/comm/ws2812b.c"
#include "services/tracer.h"

// Keyboard
#include "cpu/avr/timer0.c"
#include "cpu/avr/timer2.c"

#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__physical.c"
#include "cpu/avr/services/keyboard/keyboard.c"

#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_leds.c"
#include "comm_keyboard_simple.c"

#include "main.c"
#include "tracer__leds.c"
