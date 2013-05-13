#ifndef __ENDPOINTS__ALARM__STATE_H
#define __ENDPOINTS__ALARM__STATE_H

#include <stdint.h>


INLINE void alarm__state__broadcast(void);

INLINE void alarm__state__set_data(const uint8_t* data);


#endif