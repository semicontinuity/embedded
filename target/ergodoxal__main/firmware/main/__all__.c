#if defined(TX_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/tx_ring_buffer.c"
#endif

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
#include "cpu/avr/drivers/keyboard/keyboard__port_e__pins__mapping.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_f__pins__mapping.c"
#include "cpu/avr/drivers/keyboard/keyboard__port_g__pins__mapping.c"

#include "cpu/avr/services/keyboard/keyboard.c"
#include "cpu/avr/services/keyboard/keyboard__port_a.c"
#include "cpu/avr/services/keyboard/keyboard__port_b.c"
#include "cpu/avr/services/keyboard/keyboard__port_c.c"
#include "cpu/avr/services/keyboard/keyboard__port_d.c"
#include "cpu/avr/services/keyboard/keyboard__port_e.c"
#include "cpu/avr/services/keyboard/keyboard__port_f.c"
#include "cpu/avr/services/keyboard/keyboard__port_g.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_e__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_f__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_g__buttons.c"

// Comm
#include "comm_keyboard.c"
#include "comm_inbound.c"

#include "services/tracer__nop.c"

// Entry point
#include "main.c"
