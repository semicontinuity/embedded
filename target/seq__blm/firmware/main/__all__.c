#include <avr/io.h>

// LEDs
#include "leds.c"
#include "drivers/comm/ws2812b.c"

// Keyboard
#include "cpu/avr/timer0.c"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer0.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.c"
#include "cpu/avr/drivers/keyboard/keyboard__pins__physical.c"
#include "cpu/avr/services/keyboard/keyboard.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_leds.c"
#include "comm_keyboard_simple.c"

#include "main.c"
