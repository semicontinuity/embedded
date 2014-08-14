// =============================================================================
// Software USART driver, timer module.
// Implemented with two timers: SOFT_USART__TIMER__RX and SOFT_USART__TIMER__TX.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart__timer.h"


// =============================================================================
// RX sub-module
// =============================================================================

#if SOFT_USART__TIMER__RX==0

// Only naked ISR supported
#define TIMER0_COMPA_vect_naked             	1
#define TIMER0__COMPARE_A__INTERRUPT__ENABLED   1
#define timer0__comp_a__run                     soft_usart__rx__run

#include "cpu/avr/timer0.c"
#else
#error "Unsupported"
#endif


#define SOFT_USART__TIMER__F(t,f) timer##t##f

#define soft_usart__timer__rx__conf_initialized_delay_half_bit(t)\
    SOFT_USART__TIMER__F(t,__conf__ctc_initialized)(SOFT_USART__TIMER__F(t,__conf__ctc_compare_a_value)(F_CPU/SOFT_USART__BAUD_RATE)/2)

#define soft_usart__timer__rx__conf_started_delay_half_bit(t)\
    SOFT_USART__TIMER__F(t,__conf__ctc_started)(\
        SOFT_USART__TIMER__F(t,__conf__ctc_compare_a_value)(F_CPU/SOFT_USART__BAUD_RATE)/2, \
        SOFT_USART__TIMER__F(t,__conf__ctc_prescaler_mask)(F_CPU/SOFT_USART__BAUD_RATE)\
    )

#define soft_usart__timer__rx__conf_started_delay_full_bit(t)\
    SOFT_USART__TIMER__F(t,__conf__ctc_started)(\
        SOFT_USART__TIMER__F(t,__conf__ctc_compare_a_value)(F_CPU/SOFT_USART__BAUD_RATE), \
        SOFT_USART__TIMER__F(t,__conf__ctc_prescaler_mask)(F_CPU/SOFT_USART__BAUD_RATE)\
    )


#define soft_usart__timer__rx__init_half_bit_delay(t) do {\
    SOFT_USART__TIMER__F(t,__switch_conf)(\
        SOFT_USART__TIMER__F(t,__conf__default)(),\
        soft_usart__timer__rx__conf_initialized_delay_half_bit(t)\
    );\
} while(0)

#define soft_usart__timer__rx__start_half_bit_delay(t) do {\
    SOFT_USART__TIMER__F(t,__switch_conf)(\
        soft_usart__timer__rx__conf_initialized_delay_half_bit(t),\
        soft_usart__timer__rx__conf_started_delay_half_bit(t)\
    );\
} while(0)

#define soft_usart__timer__rx__start_full_bit_delay(t) do {\
    SOFT_USART__TIMER__F(t,__switch_conf)(\
        soft_usart__timer__rx__conf_started_delay_half_bit(t),\
        soft_usart__timer__rx__conf_started_delay_full_bit(t)\
    );\
} while(0)

#define soft_usart__timer__rx__stop(t) do {\
    SOFT_USART__TIMER__F(t,__switch_conf)(\
        soft_usart__timer__rx__conf_started_delay_full_bit(t),\
        soft_usart__timer__rx__conf_initialized_delay_half_bit(t)\
    );\
} while(0)

void soft_usart__timer__signal_start_bit_begin(void) {
    soft_usart__timer__rx__start_half_bit_delay(SOFT_USART__TIMER__RX);
}

void soft_usart__timer__signal_start_bit_middle(void) {
    soft_usart__timer__rx__start_full_bit_delay(SOFT_USART__TIMER__RX);
}

void soft_usart__timer__signal_stop_bit_middle(void) {
    soft_usart__timer__rx__stop(SOFT_USART__TIMER__RX);
}


// =============================================================================
// TX sub-module
// =============================================================================
#include "cpu/avr/drivers/comm/soft_usart__tx.h"

#if SOFT_USART__TIMER__TX==2

// Only naked ISR supported
#define TIMER2_COMPA_vect_naked                 1
#define TIMER2_COMPA_vect_no_reti               1
#define TIMER2__PERIOD                          (F_CPU / SOFT_USART__BAUD_RATE)
#define TIMER2__COMPARE_A__INTERRUPT__ENABLED   1
#define timer2__comp_a__run                     soft_usart__tx__run

#include "cpu/avr/timer2.c"

void soft_usart__timer__tx__init(void) {
    timer2__init();
}

void soft_usart__timer__signal_tx_requested(void) {
    soft_usart__tx__begin();
    timer2__start();
}

void soft_usart__timer__signal_tx_complete(void) {
    timer2__stop();
}

#else
#error "Unsupported"
#endif


// =============================================================================
// General
// =============================================================================


void soft_usart__timer__init(void) {
    soft_usart__timer__tx__init();
    soft_usart__timer__rx__init_half_bit_delay(SOFT_USART__TIMER__RX);
}
