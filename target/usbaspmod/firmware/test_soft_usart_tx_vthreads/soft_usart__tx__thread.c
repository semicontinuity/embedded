// =============================================================================
// Soft USART TX module, implemented with vthreads.
// =============================================================================
#include <stdint.h>
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer2.h"
#include "cpu/avr/asm.h"


#ifdef SOFT_USART__TX__THREAD__IP__REG
register uint8_t* soft_usart__tx__thread__ip asm(QUOTE(SOFT_USART__TX__THREAD__IP__REG));
#else
volatile uint8_t* soft_usart__tx__thread__ip;
#endif

#ifdef SOFT_USART__TX__DATA__REG
register uint8_t soft_usart__tx__data asm(QUOTE(SOFT_USART__TX__DATA__REG));
#else
volatile uint8_t soft_usart__tx__data;
#endif


void soft_usart__tx__thread__init(void) {
    VT_INIT(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    timer2__init();
}

/** Begin transmission */
void soft_usart__tx__begin(void) {
    OUT_0(SOFT_USART__TX);
}

void soft_usart__timer__signal_tx_requested(void) {
    // generate start bit
    soft_usart__tx__begin();
    timer2__start();
}


/** Request to start transmission of a byte of data */
void soft_usart__tx__write(const uint8_t data) {
    soft_usart__tx__data = data;
    soft_usart__timer__signal_tx_requested();
}


#define soft_usart__tx__thread__yield() do {\
    VT_YIELD_S(soft_usart__tx__thread, soft_usart__tx__thread__ip);\
} while(0)


VT_FUNC(soft_usart__tx__thread__function, soft_usart__tx__thread__function_attrs) {
    VT_BEGIN(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // 0x61 = 'a'
    OUT_1(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_0(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_0(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_0(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_0(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_1(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_1(SOFT_USART__TX);
    soft_usart__tx__thread__yield();
    OUT_0(SOFT_USART__TX);
    soft_usart__tx__thread__yield();

    // stop bit
    OUT_1(SOFT_USART__TX);
    soft_usart__tx__thread__yield();

    timer2__stop();
    VT_END_S(soft_usart__tx__thread);
}
