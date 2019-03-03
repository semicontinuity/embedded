// =============================================================================
// Scanner (RGB LEDs, with dedicated buffer).
// =============================================================================

#include "services/scanner__rgb_leds.h"

#if !(CONCAT(0x, OUT__LED1R_ROW__PORT) == CONCAT(0x, OUT__LED1G_ROW__PORT))
#  error "All RGB LEDs must be on the same port!"
#endif
#if !(CONCAT(0x, OUT__LED1R_ROW__PORT) == CONCAT(0x, OUT__LED1B_ROW__PORT))
#  error "All RGB LEDs must be on the same port!"
#endif
#if !(CONCAT(0x, OUT__LED1R_ROW__PORT) == CONCAT(0x, OUT__LED2R_ROW__PORT))
#  error "All RGB LEDs must be on the same port!"
#endif
#if !(CONCAT(0x, OUT__LED1R_ROW__PORT) == CONCAT(0x, OUT__LED2G_ROW__PORT))
#  error "All RGB LEDs must be on the same port!"
#endif
#if !(CONCAT(0x, OUT__LED1R_ROW__PORT) == CONCAT(0x, OUT__LED2B_ROW__PORT))
#  error "All RGB LEDs must be on the same port!"
#endif


uint8_t scanner__rgb_leds__buffer[1024];

#ifdef SCANNER__RGB_LEDS__DATA_PTR__REG
register uint8_t *scanner__rgb_leds__data_ptr asm(QUOTE(SCANNER__RGB_LEDS__DATA_PTR__REG));
#else
volatile uint8_t *scanner__rgb_leds__data_ptr;
#endif


void scanner__rgb_leds__rewind(void) {
    scanner__rgb_leds__data_ptr = scanner__rgb_leds__buffer;
}


void scanner__rgb_leds__render_column(uint8_t phase) {
//    uint8_t data = *scanner__rgb_leds__data_ptr++;
}
