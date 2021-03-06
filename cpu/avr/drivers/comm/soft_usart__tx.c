// =============================================================================
// Software USART driver, transmitter module.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart__tx.h"
#include "cpu/avr/drivers/comm/soft_usart__timer.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


DEFINE_OUT_SIGNAL(soft_usart__tx, SOFT_USART__TX);


#ifdef SOFT_USART__TX__DATA__REG
register uint8_t soft_usart__tx__data asm(QUOTE(SOFT_USART__TX__DATA__REG));
#else
volatile uint8_t soft_usart__tx__data;
#endif

#ifdef SOFT_USART__TX__INDEX__REG
register  int8_t soft_usart__tx__index asm(QUOTE(SOFT_USART__TX__INDEX__REG));
#else
volatile  int8_t soft_usart__tx__index;
#endif


/** Request transmission */
void soft_usart__tx__write(const uint8_t data) {
    // does not check for concurrent transmission
    soft_usart__tx__data = data;
    soft_usart__tx__index = -(8+1+1);   // main branch of soft_usart__tx__run() will be run 8+1 times
    soft_usart__timer__signal_tx_requested();
}

/** Begin transmission */
void soft_usart__tx__begin(void) {
    soft_usart__tx__set(0);
}


/**
 * Invoked periodically by the associated timer (if it is started)
 * with the delay, equal to 1 bit time, before every data bit, before and after stop bit.
 * During every invocation, the output pin will be driven according to the value of the corresponding bit.
 */
void soft_usart__tx__run(void) {
    // Must produce SUBI rd, 0xFF instruction that will set CARRY flag for the first bit
    ++soft_usart__tx__index;
    BREQ(soft_usart__tx__run__complete);

    // Transmitting data bits and stop bit
    uint8_t port_data = PORT_REG(SOFT_USART__TX__PORT);
    COPY_BIT(soft_usart__tx__data, 0, port_data, SOFT_USART__TX__PIN);
    PORT_REG(SOFT_USART__TX__PORT) = port_data;
    // When rotating for the 0th bit, CARRY flag is still set (after SUBI instruction), so it is rotated in.
    // Later, when 8th bit is transmitted, the value of that original CARRY flag will appear at bit 0.
    // It was 1, so logical high is output on the pin and thus the stop bit is generated.
    ROR(soft_usart__tx__data);
#if defined(SOFT_USART__TX__RUN__IN_ISR)
    RETI();
#else
    RJMP(soft_usart__tx__run__exit);
#endif

    // everything is transmitted; stop
    MARK(soft_usart__tx__run__complete);
    soft_usart__timer__signal_tx_complete();
    soft_usart__tx__on_write_complete();
#if defined(SOFT_USART__TX__RUN__IN_ISR)
    RETI();
#endif

    MARK(soft_usart__tx__run__exit);
}
