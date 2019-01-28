// =============================================================================
// Test (Soft USART)
// =============================================================================

#include "drivers/out/led_red.h"
#include "soft_usart__timer.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "cpu/avr/util/vthreads.h"


#ifdef SOFT_USART__TX__THREAD__IP__REG
register uint8_t* soft_usart__tx__thread__ip asm(QUOTE(SOFT_USART__TX__THREAD__IP__REG));
#else
volatile uint8_t* soft_usart__tx__thread__ip;
#endif

static inline void soft_usart__tx__thread__init(void) {
    VT_INIT(soft_usart__tx__thread, soft_usart__tx__thread__ip);
}


void soft_usart__tx__thread__run(void) {
    VT_BEGIN(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    for(;;) {
        // 15 bits idle (1)
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

        // START
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

        // 8 bits: 0010 0001 LSB first
        led_red__set(1);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(1);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
        led_red__set(0);
        VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

        // STOP
        led_red__set(1);
        VT_GOTO(soft_usart__tx__thread, soft_usart__tx__thread__ip, BEGIN);
    }

    VT_UNREACHEABLE_END(soft_usart__tx__thread);
}


int main(void) {
    led_red__init();
    led_red__set(1);

    soft_usart__tx__thread__init();
    soft_usart__timer__init();

    soft_usart__timer__start();

    sei();
    for(;;) {
    }

    return 0;
}
