#ifndef __ENDPOINTS__ALARM__STATE_H
#define __ENDPOINTS__ALARM__STATE_H

#include <stdint.h>


INLINE uint8_t alarm__state__get_data(uint8_t **data);

INLINE void alarm__state__set_data(const uint8_t* data);


#endif