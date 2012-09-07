// =============================================================================
// Memory
// =============================================================================

#ifndef __CPU_AVR_MEMORY_H
#define __CPU_AVR_MEMORY_H

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 


inline static void memory__copy(void* dst, ) {
    // Enable interrupt from INT0
    EIMSK |= (1<<INT0);
}


#elif defined(__AVR_ATmega8__)


inline static void int0__init(void) {
    // pullup?
    MCUCR = (1<<ISC01);
}


inline static void int0__start(void) {
    // Enable interrupt from INT0
    GICR  |= (1<<INT0);	// enable external interrupt from INT0 pin
}

#else

#   error "Unsupported MCU"

#endif


INLINE void int0__run(void) int0__run__attrs;

#endif