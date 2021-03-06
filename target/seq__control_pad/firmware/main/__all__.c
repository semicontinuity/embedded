#include <avr/io.h>

#if defined(TX_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/tx_ring_buffer.c"
#endif

// LED data
#include "data.c"

// I/O matrix
//#include "cpu/avr/timer0.c"
//#include "drivers/io_matrix__scanner__thread__timer__timer0.c"
//#include "drivers/io_matrix__in.c"
//#include "io_matrix__scanner__thread.c"
#include "cpu/avr/timer1.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__in.c"
#include "io_matrix__scanner__thread.c"


// Keyboard
#include "cpu/avr/timer0.c"
#include "cpu/avr/timer2.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__matrix.c"
//#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer2.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b.c"

#include "cpu/avr/services/keyboard/keyboard.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"


// Encoder
#include "drivers/in/encoder__step.c"
#include "drivers/in/encoder0.c"
#include "drivers/in/encoder0__switch.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_events_simple.c"
#include "comm_leds.c"
#if defined(TX_RING_BUFFER__SIZE)
#  include "comm_keyboard.c"
#else
#  include "comm_keyboard_simple.c"
#endif
#include "comm_encoder.c"

// Tracing
#include "services/tracer__nop.c"

// Entry point
#include "main.c"
