#if defined(TX_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/tx_ring_buffer.c"
#endif

// LED data
#include "data.c"

// I/O matrix
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h"
#include "cpu/avr/drivers/io_matrix/io_matrix__in.c"
#include "io_matrix__scanner__thread.c"

// Keyboard
#include "cpu/avr/timer0.c"
#include "cpu/avr/timer2.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__matrix.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b.c"

#include "cpu/avr/services/keyboard/keyboard.c"
#include "cpu/avr/services/keyboard/keyboard__port_a.c"
#include "cpu/avr/services/keyboard/keyboard__port_b.c"
#include "cpu/avr/services/keyboard/keyboard__port_c.c"
#include "cpu/avr/services/keyboard/keyboard__port_d.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__encoders.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__encoders.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__encoders.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__encoders.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_leds.c"
#if defined(TX_RING_BUFFER__SIZE)
#  include "comm_keyboard.c"
#else
#  include "comm_events_simple.c"
#endif

#include "comm_encoder_queues.c"
#include "comm_buttons_queues.c"

#include "services/tracer__usart0.c"

// Entry point
#include "main.c"
