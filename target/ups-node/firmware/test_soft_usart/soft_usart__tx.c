// =============================================================================
// Soft USART TX driver.
// =============================================================================

#include "soft_usart__tx.h"
#include "soft_usart__timer.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/vthreads.h"

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


void soft_usart__tx__thread__start(void) {
    VT_INIT(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // render start bit
    OUT_0(SOFT_USART__TX);
    soft_usart__timer__tx__start();
}


void soft_usart__tx__thread__run(void) {
    VT_BEGIN(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data0 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 0, pin_data0, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data0;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data1 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 1, pin_data1, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data1;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data2 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 2, pin_data2, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data2;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data3 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 3, pin_data3, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data3;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data4 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 4, pin_data4, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data4;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data5 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 5, pin_data5, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data5;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data6 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 6, pin_data6, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data6;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    uint8_t pin_data7 = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 7, pin_data7, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = pin_data7;
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // render stop bit
    OUT_1(SOFT_USART__TX);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    soft_usart__timer__tx__stop();
    soft_usart__tx__on_complete();
    VT_UNREACHEABLE_END(soft_usart__tx__thread);
}
