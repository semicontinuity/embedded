// =============================================================================
// Tests soft USART transmission.
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>

#include "soft_usart__timer.h"
#include "soft_usart__tx__thread.h"
#include "soft_usart__tx.h"



int main(void) {
    soft_usart__tx__pin__init();
    soft_usart__timer__init();

    sei();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    for(;;) {
        while (soft_usart__tx__thread__is_runnable());
        soft_usart__tx__send('H');
        while (soft_usart__tx__thread__is_runnable());
        soft_usart__tx__send('e');
        while (soft_usart__tx__thread__is_runnable());
        soft_usart__tx__send('l');
        while (soft_usart__tx__thread__is_runnable());
        soft_usart__tx__send('l');
        while (soft_usart__tx__thread__is_runnable());
        soft_usart__tx__send('o');

        _delay_ms(500);
    }
#pragma clang diagnostic pop

    return 0;
}
