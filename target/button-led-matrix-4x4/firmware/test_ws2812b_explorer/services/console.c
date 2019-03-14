#include <cpu/avr/usart0.h>
#include "services/console.h"

void console__init(void) {
    usart0__init();
}

void console__start(void) {
}
