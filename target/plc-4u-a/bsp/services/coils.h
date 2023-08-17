#ifndef __COILS_H
#define __COILS_H

#include <stdint.h>
#include <stdbool.h>


#ifndef coils__byte0
extern uint8_t coils__byte0;
#endif

#ifndef coils__byte1
extern uint8_t coils__byte1;
#endif

#ifndef coils__byte2
extern uint8_t coils__byte2;
#endif

#ifndef coils__byte3
extern uint8_t coils__byte3;
#endif

#ifndef coils__byte4
extern uint8_t coils__byte4;
#endif


inline bool __attribute__((always_inline)) coils__get(uint8_t coil);
inline void __attribute__((always_inline)) coils__set(uint8_t coil, bool value);

void coils__init(void);


#endif
