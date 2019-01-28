// =============================================================================
// Soft USART RX driver.
// =============================================================================

#include "soft_usart__rx.h"
#include "soft_usart__timer.h"
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


void soft_usart__rx__init(void) {
    ENABLE_PULLUP(SOFT_USART__RX);
}

void soft_usart__rx__thread__start(void) {
    soft_usart__rx__detector__stop();
    soft_usart__timer__rx__start();
    VT_INIT(soft_usart__rx__thread, soft_usart__rx__thread__ip);
}

void soft_usart__rx__start(void) {
    soft_usart__rx__thread__start();
}

/**
 * Soft USART RX thread.
 * Not using instructions like SBR, because they clobber many flags,
 * # and the flags register is NOT saved.
 * Clobbers T bit.
 */
void soft_usart__rx__thread__run(void) {
#ifdef TEMP_REG
    register uint8_t temp_reg asm(QUOTE(TEMP_REG));
#else
    uint8_t temp_reg;
#endif

    VT_BEGIN(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    // In the middle of start bit - value not checked
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 0);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 1);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 2);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 3);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 4);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 5);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 6);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    __IN(temp_reg,PORT_REG(SOFT_USART__RX__PORT));
    COPY_BIT(temp_reg, SOFT_USART__RX__PIN, soft_usart__rx__data, 7);
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    // In the middle of stop bit - value not checked
    soft_usart__timer__rx__stop();
    soft_usart__rx__detector__start(); // not at the very end of the bit, but will do for a while
    soft_usart__rx__on_data();

    VT_UNREACHEABLE_END(soft_usart__rx__thread);
}
