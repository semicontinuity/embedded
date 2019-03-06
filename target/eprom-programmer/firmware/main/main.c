// =============================================================================
// Interactive console for bit-banging on all ports except USART.
// =============================================================================

#include "services/console.h"
#include "cpu/avr/usart0.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


static void application__init(void) {
    console__init();
}


int main(void) {
    application__init();

    console__run();
}

