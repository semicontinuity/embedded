#include "device.h"

#include "can_selector.h"
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
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();


    usart_tx_q__init();
    usart_tx_thread__init();
    usart_rx_thread__init();

    can_tx_q__init();


    spi__init(SPI_CLKDIV_128);

    can_selector__init();

    mcp251x__init();

    can__init();
    can__start();

    can_service__init();
    can_service__start();


    usart_rx_thread__enabled__set(1);

    sei();
    for(;;);
}
