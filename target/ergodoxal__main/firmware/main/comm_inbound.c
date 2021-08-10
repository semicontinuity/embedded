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
void comm_inbound__thread__handle_event(uint8_t event) {
    __asm__ __volatile__("comm_inbound__thread__handle_event:");
    led_a__copy(event, 0);
    led_b__copy(event, 1);
    led_c__copy(event, 2);
    led_d__copy(event, 3);
    led_e__copy(event, 4);
    led_f__copy(event, 5);
    led_g__copy(event, 6);
}


void comm_inbound__thread__start(void) {
    usart0__rx__enabled__set(1);
}

bool comm_inbound__thread__is_runnable(void) {
    return __builtin_expect(usart0__rx__complete__value__get(), false);
}

void comm_inbound__thread__run(void) {
    __asm__ __volatile__("comm_inbound__thread__run:");
    comm_inbound__thread__handle_event(usart0__getc());
}
