#include <avr/io.h>

// Encoders
#include "drivers/in/encoder__step.c"

//#include "drivers/in/encoders__port_a.c"

#include "drivers/in/encoder0.c"
#include "drivers/in/encoder0__switch.c"
#include "drivers/in/encoder1.c"
#include "drivers/in/encoder1__switch.c"
#include "drivers/in/encoder2.c"
#include "drivers/in/encoder2__switch.c"
#include "drivers/in/encoder3.c"
#include "drivers/in/encoder3__switch.c"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a__flag.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b__flag.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a__flag.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b__flag.c"

// I2C Comm
#include "cpu/avr/twi.c"
#include "twi_slave__handler.c"
#include "comm_events_simple.c"
#include "comm_encoder_queues.c"
#include "comm_buttons_queues.c"

// Entry point
#include "main.c"
