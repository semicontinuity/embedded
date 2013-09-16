// =============================================================================
// vthreads test - blinking LED.
// =============================================================================
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer1.h"
#include "cpu/avr/int0.h"
#include "cpu/avr/int1.h"


// Timer 1
// -----------------------------------------------------------------------------

#define TIMER1_STOPPED (TIMER1_CONF_DEFAULT)
#define TIMER1_RUNNING (TIMER1_CONF_WGM_CTC_USE_OCRA | TIMER1_CONF_PRESCALER_1024)


// Blink thread
// -----------------------------------------------------------------------------

register vthread_ip_t blink_thread__ip asm("r30");


static inline void blink_thread__init(void) {
    VT_INIT(blink_thread, blink_thread__ip);
}

static inline uint8_t blink_thread__is_runnable(void) {
    return !timer1__is_running();
}

static inline void blink_thread__wait(const uint16_t cycles) {
    timer1__compare_a__value__set(cycles);
    timer1__switch_conf(TIMER1_STOPPED, TIMER1_RUNNING);
}

static inline void blink_thread__notify(void) {
    timer1__switch_conf(TIMER1_RUNNING, TIMER1_STOPPED);
    timer1__value__set(0);
}

static inline void blink_thread__force_off(void) {
    VT_SEEK(blink_thread, blink_thread__ip, OFF);
}

static inline void blink_thread__force_on(void) {
    VT_SEEK(blink_thread, blink_thread__ip, ON);
}


void blink_thread__run(void) {
    VT_BEGIN(blink_thread, blink_thread__ip);

    VT_MARK(blink_thread, OFF);
    PORTC &= ~(1<<0);
    blink_thread__wait(64000);	// about 8 secs
    VT_YIELD(blink_thread, blink_thread__ip);  // next line will be executed in 8 seconds


    VT_MARK(blink_thread, ON);
    PORTC |= (1<<0);
    blink_thread__wait(32000);	// about 4 secs
    VT_YIELD(blink_thread, blink_thread__ip);  // next line will be executed in 4 seconds

    VT_END(blink_thread);
}


// ISR
// -----------------------------------------------------------------------------


ISR(INT0_vect, ISR_NAKED) {
    blink_thread__force_on();
    blink_thread__notify();
    asm("reti");
}

ISR(INT1_vect, ISR_NAKED) {
    blink_thread__force_off();
    blink_thread__notify();
    asm("reti");
}

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
    blink_thread__notify();
    asm("reti");
}


// main
// -----------------------------------------------------------------------------

int main(void) {
    // pin C0: output
    DDRC |= (1<<0);

    // INT0 & INT1: interrups on falling edge
    int0__init();
    int0__start();
    int1__init();
    int1__start();

    // timer
    timer1__compare_a__interrupt__enabled__set(1);

    // blink thread
    blink_thread__init();

    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    for(;;) {
        if (blink_thread__is_runnable()) {
            blink_thread__run();
        }
        else {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}
