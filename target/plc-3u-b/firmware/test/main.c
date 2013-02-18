#include <avr/interrupt.h>

#include "cpu/avr/spi.h"

#include "console_service.h"

//__attribute__ ((noreturn))
int main(void)
{
    console_service__init();

    spi__init(SPI_CLKDIV_16);

    console_service__run();
}
