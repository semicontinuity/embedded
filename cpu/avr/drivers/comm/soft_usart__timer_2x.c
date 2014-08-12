// =============================================================================
// Software USART driver, timer module.
// Implemented with two timers: SOFT_USART__TIMER__RX and SOFT_USART__TIMER__TX.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart__timer.h"

#if SOFT_USART__TIMER__RX==0
#include "cpu/avr/timer0.h"
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


void soft_usart__timer__init(void) {
    soft_usart__timer__rx__init_half_bit_delay(SOFT_USART__TIMER__RX);
}

void soft_usart__timer__signal_start_bit_begin(void) {
    soft_usart__timer__rx__start_half_bit_delay(SOFT_USART__TIMER__RX);
}

void soft_usart__timer__signal_start_bit_middle(void) {
    soft_usart__timer__rx__start_full_bit_delay(SOFT_USART__TIMER__RX);
}

void soft_usart__timer__signal_stop_bit_middle(void) {
    soft_usart__timer__rx__stop(SOFT_USART__TIMER__RX);
}
