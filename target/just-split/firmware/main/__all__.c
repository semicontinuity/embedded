/*
#if defined(TX_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/tx_ring_buffer.c"
#endif
*/

#if defined(GP_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/gp_ring_buffer.c"
#endif

#include "leds_bar__data.c"
#include "leds_bar__wdt.c"

// I/O matrix
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c"
#include "drivers/io_matrix/io_matrix__in.c"
#include "io_matrix__scanner__thread.c"

// Keyboard
#include "cpu/avr/timer0.c"
#include "cpu/avr/timer2.c"

#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__a__timer0a.c"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__b__timer0b.c"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__c__timer2a.c"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__d__timer2b.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__matrix.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c"

#include "cpu/avr/services/keyboard/keyboard.c"
#include "cpu/avr/services/keyboard/keyboard__port_a.c"
#include "cpu/avr/services/keyboard/keyboard__port_b.c"
#include "cpu/avr/services/keyboard/keyboard__port_c.c"
#include "cpu/avr/services/keyboard/keyboard__port_d.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"

#include "keyboard_handler.c"

// Comm
#include "comm_usart_outbound__thread.c"
#include "comm_usart_inbound__thread.c"

#include "comm_twi__outbound.c"
#include "comm_twi__inbound.c"

#include "twi_slave__handler.c"

#include "services/tracer__nop.c"

// Entry point
#include "main.c"
