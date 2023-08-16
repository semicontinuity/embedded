#ifndef __INTERNAL_COILS_H
#define __INTERNAL_COILS_H

#include <stdint.h>
#include <stdbool.h>


#ifndef internal_coils__byte0
extern uint8_t internal_coils__byte0;
#endif

#ifndef internal_coils__byte1
extern uint8_t internal_coils__byte1;
#endif


inline bool __attribute__((always_inline)) internal_coils__get(uint8_t coil);
inline void __attribute__((always_inline)) internal_coils__set(uint8_t coil, bool value);

void internal_coils__init(void);


#endif
