#ifndef __SOFT_USART__TX_THREAD_H
#define __SOFT_USART__TX_THREAD_H

#include "cpu/avr/util/vthreads.h"
#include "soft_usart__tx__pin.h"


void soft_usart__tx__thread__on_finish(void);


#ifdef SOFT_USART__TX__THREAD__IP__REG
register uint8_t* soft_usart__tx__thread__ip asm(QUOTE(SOFT_USART__TX__THREAD__IP__REG));
#else
volatile uint8_t* soft_usart__tx__thread__ip;
#endif

static volatile uint8_t soft_usart__tx__thread__data;


void soft_usart__tx__thread__data__set(const uint8_t data) {
    soft_usart__tx__thread__data = data;
}


void soft_usart__tx__thread__init(void) {
    VT_INIT(soft_usart__tx__thread, soft_usart__tx__thread__ip);
}


static void soft_usart__tx__thread__send_bit(const uint8_t mask) {
    uint8_t data = soft_usart__tx__thread__data;
    if (data & mask)
        soft_usart__tx__pin__set(1);
    else
        soft_usart__tx__pin__set(0);
}

void soft_usart__tx__thread__run(void) {
    VT_BEGIN(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // START
    soft_usart__tx__pin__set(0);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    soft_usart__tx__thread__send_bit(0x01);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x02);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x04);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x08);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    soft_usart__tx__thread__send_bit(0x10);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x20);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x40);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);
    soft_usart__tx__thread__send_bit(0x80);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    // STOP
    soft_usart__tx__pin__set(1);
    VT_YIELD(soft_usart__tx__thread, soft_usart__tx__thread__ip);

    VT_END(soft_usart__tx__thread);

    soft_usart__tx__thread__on_finish();
}

#endif
