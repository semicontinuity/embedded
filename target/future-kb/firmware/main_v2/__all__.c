#if defined(GP_RING_BUFFER__SIZE)
// TX ring buffer first for 256-byte alignment
#  include "services/gp_ring_buffer.c"
#endif

// Keyboard
#include "cpu/avr/timer1.c"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer1.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__physical.c"

#include "cpu/avr/services/keyboard/keyboard.c"
#include "cpu/avr/services/keyboard/keyboard__port_a.c"
#include "cpu/avr/services/keyboard/keyboard__port_b.c"
#include "cpu/avr/services/keyboard/keyboard__port_c.c"
#include "cpu/avr/services/keyboard/keyboard__port_d.c"

#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.c"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.c"

#include "keyboard_handler.c"

// Comm
#include "comm_usart_outbound__thread.c"

#include "services/tracer__nop.c"

// Entry point
#include "main.c"
