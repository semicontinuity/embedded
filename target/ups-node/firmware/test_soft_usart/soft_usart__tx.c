// =============================================================================
// Soft USART TX driver.
// =============================================================================

#include <avr/interrupt.h>
#include "soft_usart__tx.h"
#include "soft_usart__timer.h"
#include "temp_reg.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/vthreads.h"

#ifdef SOFT_USART__TX__THREAD__IP__REG
register uint8_t* soft_usart__tx__thread__ip asm(QUOTE(SOFT_USART__TX__THREAD__IP__REG));
#else
volatile uint8_t* soft_usart__tx__thread__ip;
#endif

#ifndef SOFT_USART__TX__DATA__REG
volatile uint8_t soft_usart__tx__data;
#endif


void soft_usart__tx__init(void) {
    USE_AS_OUTPUT(SOFT_USART__TX);
}


void soft_usart__tx__thread__start(void) {
    VT_INIT(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // render start bit
    OUT_0(SOFT_USART__TX);
    soft_usart__timer__tx__start();
}

void soft_usart__tx__start(void) {
    soft_usart__tx__thread__start();
}


void soft_usart__tx__thread__run(void) {
    VT_BEGIN(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 0, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 1, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 2, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 3, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 4, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 5, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 6, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__TX__PORT));
    COPY_BIT(soft_usart__tx__data, 7, temp_reg, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = temp_reg;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // render stop bit
    OUT_1(SOFT_USART__TX);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

//            temp_reg = 1;
//            DDRD=_SFR_IO_ADDR(DDRD);
//    TIMER2__COMPARE_B__INTERRUPT__ENABLE__HOST = _SFR_IO_ADDR(TIMER2__COMPARE_B__INTERRUPT__ENABLE__HOST);
    soft_usart__timer__tx__stop();
    soft_usart__tx__on_complete();
    VT_UNREACHEABLE_END(soft_usart__tx__thread);
}
