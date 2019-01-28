#include "drivers/out/mcp251x_select.h"
#include "can_service.h"
#include "can_tx_q.h"
#include "usart_tx.h"
#include "usart_tx_q.h"
#include "usart_rx.h"

#include "can.h"

#include <util/delay.h>
#include <util/atomic.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"
#include "cpu/avr/usart0.h"

#include "cpu/avr/drivers/net/can/mcp251x/conf.h"



//int main(void) __attribute__ ((noreturn));
int main(void)
{
    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);


    usart_tx_q__init();
    usart_tx_thread__init();
    usart_rx_thread__init();

    can_tx_q__init();


    spi__init(SPI_CLKDIV_128);

    mcp251x_select__init();

    mcp251x__init();

    can__init();
    can__start();

    can_service__init();
    can_service__start();


    usart_rx_thread__enabled__set(1);

    sei();
    for(;;);
}
