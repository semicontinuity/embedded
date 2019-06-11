#include <avr/io.h>

// Encoder
#include "drivers/in/encoder__step.c"
#include "drivers/in/encoder0.c"
#include "drivers/in/encoder0__switch.c"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a__flag.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_events_simple.c"
#include "comm_encoder.c"

// Entry point
#include "main.c"
