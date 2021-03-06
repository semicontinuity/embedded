#include <avr/io.h>

#include "cpu/avr/pin_change_int0.c"
#include "cpu/avr/pin_change_int1.c"
#include "cpu/avr/pin_change_int2.c"
#include "cpu/avr/timer0.c"
#include "cpu/avr/drivers/usart0__tx.c"

#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer0.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__physical.c"
#include "services/tx_ring_buffer.c"
#include "keyboard__interrupts.c"

#include "main.c"
