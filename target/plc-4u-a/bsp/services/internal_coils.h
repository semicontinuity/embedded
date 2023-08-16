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


void internal_coil__0__set(bool value);
bool internal_coil__0__get(void);

void internal_coil__1__set(bool value);
bool internal_coil__1__get(void);

void internal_coil__2__set(bool value);
bool internal_coil__2__get(void);

void internal_coil__3__set(bool value);
bool internal_coil__3__get(void);

void internal_coil__4__set(bool value);
bool internal_coil__4__get(void);

void internal_coil__5__set(bool value);
bool internal_coil__5__get(void);

void internal_coil__6__set(bool value);
bool internal_coil__6__get(void);

void internal_coil__7__set(bool value);
bool internal_coil__7__get(void);


void internal_coil__8__set(bool value);
bool internal_coil__8__get(void);

void internal_coil__9__set(bool value);
bool internal_coil__9__get(void);

void internal_coil__a__set(bool value);
bool internal_coil__a__get(void);

void internal_coil__b__set(bool value);
bool internal_coil__b__get(void);

void internal_coil__c__set(bool value);
bool internal_coil__c__get(void);

void internal_coil__d__set(bool value);
bool internal_coil__d__get(void);

void internal_coil__e__set(bool value);
bool internal_coil__e__get(void);

void internal_coil__f__set(bool value);
bool internal_coil__f__get(void);


bool internal_coils__get(uint8_t coil);
inline void internal_coils__set(uint8_t coil, bool value);

void internal_coils__init(void);


#endif
