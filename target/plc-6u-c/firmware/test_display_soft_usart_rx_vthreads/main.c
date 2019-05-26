// =============================================================================
// Simple test for software USART and display.
// =============================================================================

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#include "soft_usart__timer.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/int0.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/drivers/display/segment/static2.h"


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


void start_bit_detected(void) {
    int0__stop();
    VT_INIT(soft_usart__rx__thread, soft_usart__rx__thread__ip);
    soft_usart__timer__reset();
    soft_usart__timer__start();
}


void soft_usart__rx__thread__run(void) {
    VT_BEGIN(soft_usart__rx__thread, soft_usart__rx__thread__ip);

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
    VT_YIELD(soft_usart__rx__thread, soft_usart__rx__thread__ip);

    // In the middle of stop bit
    soft_usart__timer__stop();        
    int0__start();
    
    display__render_packed(soft_usart__rx__data);

    VT_UNREACHEABLE_END(soft_usart__rx__thread);
}


int main(void) {
    display__init();
    soft_usart__timer__init();
    int0__init();
    
    int0__start();

    sei();    
    for(;;) {
    }

    return 0;
}
