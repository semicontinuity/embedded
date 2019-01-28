#ifndef __USART_H
#define __USART_H


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)


#define XPLUS_TO_USART() do {           \
  __asm__ __volatile__ (                \
    "ld	   __tmp_reg__, X+	\n\t"       \
    "sts   0x00C6, __tmp_reg__	\n\t"   \
  );                                    \
} while(0)


#define USART_TO_YPLUS() do {           \
  __asm__ __volatile__ (                \
    "lds   __tmp_reg__, 0x00C6	\n\t"   \
    "st	   Y+, __tmp_reg__	\n\t"       \
  );                                    \
} while(0)


#else
    #error "Unsupported MCU"
#endif


#endif