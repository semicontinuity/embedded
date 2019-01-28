#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"
#include "cpu/avr/usart1.h"
#include "cpu/avr/usart1__rx_polled.h"


#define USART1_CONF_ISO_7816 (  \
    USART1_CONF_RX_ENABLED      \
  | USART1_CONF_TX_ENABLED      \
  | USART1_CONF_MODE_ASYNC      \
  | USART1_CONF_PARITY_EVEN     \
  | USART1_CONF_STOP_BITS_2     \
  | USART1_CONF_CHAR_SIZE_8_BIT)


void debug__putc(char c) {
    terminal__putc(c);
}

inline uint8_t debug__lower_nibble_to_hex(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return value += '0';
}

// Prefer to spend flash and CPU, save RAM.
inline void debug__print_byte_as_hex(const uint8_t value) {
    debug__putc(debug__lower_nibble_to_hex(value >> 4));
    debug__putc(debug__lower_nibble_to_hex(value & 0x0F));
}


int main(int argc, char **argv) {

    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    USE_AS_OUTPUT(SMARTCARD_RES);
    OUT_1(SMARTCARD_RES);

    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

    terminal__init();


    USE_AS_OUTPUT(USART1_RTS);
    OUT_0(USART1_RTS);

    // Smartcard is clocked with F_SC=F_CPU/4 frequency.
    // According to ISO 7816, the initial smartcard baudrate divisor is 372,
    // so F_CPU is divided by 372*4.
    usart1__divisor__set((4*372)/16 - 1);
    usart1__switch_conf(USART1_CONF_DEFAULT, USART1_CONF_ISO_7816);

    OUT_0(SMARTCARD_RES);
    _delay_ms(30);  // takes longer?
    OUT_1(SMARTCARD_RES);

    while(1) {
        char c = usart1__in__read();
        debug__print_byte_as_hex(c);
    }
    return 0;
}
