// =============================================================================
// Soft USART RX driver.
// =============================================================================
#include "soft_usart__rx.h"
#include "soft_usart__timer.h"
#include "temp_reg.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/util/vthreads.h"


#ifdef SOFT_USART__RX__THREAD__IP__REG
register uint8_t* soft_usart__rx__thread__ip asm(QUOTE(SOFT_USART__RX__THREAD__IP__REG));
#else
volatile uint8_t* soft_usart__rx__thread__ip;
#endif

#ifdef SOFT_USART__RX__DATA__REG
register uint8_t soft_usart__rx__data asm(QUOTE(SOFT_USART__RX__DATA__REG));
#else
volatile uint8_t soft_usart__rx__data;
#endif


void soft_usart__rx__detector__start(void);
void soft_usart__rx__detector__stop(void);


void soft_usart__rx__thread__start(void) {
    soft_usart__rx__detector__stop();
    soft_usart__timer__rx__start();
    VT_INIT(soft_usart__rx__thread, soft_usart__rx__thread__ip);
}

/**
 * Soft USART RX thread.
 * Not using instructions like SBR, because they clobber many flags,
 * # and the flags register is NOT saved.
 * Clobbers T bit.
 */
void soft_usart__rx__thread__run(void) {
    VT_BEGIN(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    // In the middle of start bit
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

/*
    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 0);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 1);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 2);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 3);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 4);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 5);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 6);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    temp_reg = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 7);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);
*/

    uint8_t pin_data0 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data0, SOFT_USART__RX__PIN, soft_usart__rx__data, 0);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data1 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data1, SOFT_USART__RX__PIN, soft_usart__rx__data, 1);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data2 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data2, SOFT_USART__RX__PIN, soft_usart__rx__data, 2);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data3 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data3, SOFT_USART__RX__PIN, soft_usart__rx__data, 3);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data4 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data4, SOFT_USART__RX__PIN, soft_usart__rx__data, 4);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data5 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data5, SOFT_USART__RX__PIN, soft_usart__rx__data, 5);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data6 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data6, SOFT_USART__RX__PIN, soft_usart__rx__data, 6);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    uint8_t pin_data7 = PIN_REG(SOFT_USART__RX__PORT);
    COPY_BIT(pin_data7, SOFT_USART__RX__PIN, soft_usart__rx__data, 7);
    soft_usart__rx__on_data();
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    // In the middle of stop bit
    soft_usart__timer__rx__stop();
    soft_usart__rx__detector__start();

    VT_UNREACHEABLE_END(soft_usart__rx__thread);
}
