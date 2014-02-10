#include "main.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/int0.c"
#include "cpu/avr/timer0.c"
#include "cpu/avr/drivers/usart0__rx.c"
#include "cpu/avr/drivers/usart0__tx.c"

#include "drivers/io/leds_tap.c"
#include "drivers/io/buttons_tap.c"
#include "drivers/io/lcd_tap.c"

#include "services/buttons_scanner.c"
#include "services/leds_scanner.c"
#include "services/tx_ring_buffer.c"

#include "main.c"
