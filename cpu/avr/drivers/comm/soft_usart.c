// =============================================================================
// Software USART driver.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart.h"
#include "cpu/avr/drivers/comm/soft_usart__rx.h"
#include "cpu/avr/drivers/comm/soft_usart__timer.h"

void soft_usart__init(void) {
   soft_usart__timer__init();
   soft_usart__rx__init();
}

void soft_usart__start(void) {
   soft_usart__rx__start();
}

void soft_usart__stop(void) {
   soft_usart__rx__stop();
}
