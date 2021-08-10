#include "comm_inbound.h"

#include <cpu/avr/usart0.h>

#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>
#include <drivers/out/led_c.h>
#include <drivers/out/led_d.h>
#include <drivers/out/led_e.h>
#include <drivers/out/led_f.h>
#include <drivers/out/led_g.h>


void comm_inbound__init(void) {
    led_a__init();
    led_b__init();
    led_c__init();
    led_d__init();
    led_e__init();
    led_f__init();
    led_g__init();
}


// comm_inbound__thread:
// receives and interprets bytes from USART
// runs in the context of main thread
// -----------------------------------------------------------------------------


void comm_inbound__thread__start(void) {
    usart0__rx__enabled__set(1);
}

bool comm_inbound__thread__is_runnable(void) {
    return __builtin_expect(usart0__rx__complete__value__get(), false);
}

void comm_inbound__thread__run(void) {
    __asm__ __volatile__("comm_inbound__thread__run:");
    uint8_t event = usart0__getc();
}
