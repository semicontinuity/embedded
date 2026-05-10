// =============================================================================
// Remote switch EEPROM-based configuration.
// =============================================================================

#include "services/eeprom_config.h"

#include "cpu/avr/eeprom.h"
#include "cpu/avr/usart0.h"
#include "services/buttons_handler.h"

#include <avr/pgmspace.h>

#define EEPROM_ADDRESS__BAUD_RATE (0)

// better to use U2X mode, it is more accurate
#define USART_DIVISORS__COUNT (15)
static const uint16_t PROGMEM USART_DIVISORS[USART_DIVISORS__COUNT] = {
    [BUTTONS_HANDLER__STATE(1, 1, 1, 0)] = USART0_DIVISOR(1200L),
    [BUTTONS_HANDLER__STATE(1, 1, 0, 1)] = USART0_DIVISOR(2400L),
    [BUTTONS_HANDLER__STATE(1, 1, 0, 0)] = USART0_DIVISOR(4800L),
    [BUTTONS_HANDLER__STATE(1, 0, 1, 1)] = USART0_DIVISOR(9600L),
    [BUTTONS_HANDLER__STATE(1, 0, 1, 0)] = USART0_DIVISOR(14400L),
    [BUTTONS_HANDLER__STATE(1, 0, 0, 1)] = USART0_DIVISOR(19200L),
    [BUTTONS_HANDLER__STATE(1, 0, 0, 0)] = USART0_DIVISOR(28800L),
    [BUTTONS_HANDLER__STATE(0, 1, 1, 1)] = USART0_DIVISOR(31250L),
    [BUTTONS_HANDLER__STATE(0, 1, 1, 0)] = USART0_DIVISOR(38400L),
    [BUTTONS_HANDLER__STATE(0, 1, 0, 1)] = USART0_DIVISOR(57600L),
    [BUTTONS_HANDLER__STATE(0, 1, 0, 0)] = USART0_DIVISOR(62500L),
    [BUTTONS_HANDLER__STATE(0, 0, 1, 1)] = USART0_DIVISOR(76800L),
    [BUTTONS_HANDLER__STATE(0, 0, 1, 0)] = USART0_DIVISOR(115200L),
    [BUTTONS_HANDLER__STATE(0, 0, 0, 1)] = USART0_DIVISOR(125000L),
    [BUTTONS_HANDLER__STATE(0, 0, 0, 0)] = USART0_DIVISOR(250000L)
};


// If some buttons are pressed, use buttons combination to specify baud rate, and save it to EEPROM.
// Otherwise, use configuration, saved in EEPROM
uint16_t config__get_usart_divisor(void) {
    __asm__ __volatile__( "main__config:");

    uint8_t buttons_state = buttons_handler__to_state(buttons_handler__read_state_raw());
    if (buttons_state < USART_DIVISORS__COUNT) {
        eeprom__write_byte(EEPROM_ADDRESS__BAUD_RATE, buttons_state);
        // wait until all buttons are depressed
        while (buttons_handler__read_state_raw() != BUTTONS_HANDLER__RAW_STATE__ALL_DEPRESSED);
    } else {
        buttons_state = eeprom__read_byte(EEPROM_ADDRESS__BAUD_RATE);
        if (buttons_state >= USART_DIVISORS__COUNT) {
            buttons_state = CONFIG__FALLBACK_BUTTONS_STATE; // if value in EEPROM was corrupted
        }
    }
    return pgm_read_word(&USART_DIVISORS[buttons_state]);
}
